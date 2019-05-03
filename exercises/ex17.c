#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/******************************************
 * C-Preprocessor Constants Definition
 *****************************************/ 
#define MAX_DATA 512
#define MAX_ROWS 100


/******************************************
 * Struct: Address 
 * ----------------------------------------
 * Contains information that belongs to
 * a contact
 *****************************************/ 
struct Address 
{
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

/******************************************
 * Struct: Database
 * ----------------------------------------
 * Contains MAX_ROWS numbers of addresses
 *****************************************/ 
struct Database
{ 
  struct Address rows[MAX_ROWS];
};

/******************************************
 * Struct: Connection
 * ----------------------------------------
 * Contains the file in which the database
 * is stored and the main database struct
 *****************************************/ 
struct Connection
{
  FILE *file;
  struct Database *db;
};


/******************************************
 * Function: die
 * ----------------------------------------
 * Prints an error message and quits 
 * the programm
 *****************************************/ 
void die(const char *message)
{
  if (errno) {
    perror(message);
  } 
  else { 
    printf("ERROR: %s\n", message);
  }

  exit(1);
}
  

/******************************************
 * Function: Address_print
 * ----------------------------------------
 * Prints the information for a given
 * address struct
 *****************************************/ 
void Address_print(struct Address *addr)
{
  printf("%3d|%10s|\t%40s|\n", addr->id, addr->name, addr->email);
}


/******************************************
 * Function: Database_load
 * ----------------------------------------
 * Calls the function 
 * "fread(*ptr, size, nmemb, *stream)"
 * which reads <nmemb> of data, each <size>
 * bytes long, from the "stream" of type
 * FILE and storing them at the loaction
 * <ptr>
 *
 * Loads the database from file, stored
 * in Connection *conn, an copies it 
 * into Connection conn
 *
 *****************************************/ 
void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die("Failed to load database.\n");
}


/******************************************
 * Function: Database_open
 * ----------------------------------------
 * Allocates memory for a new connection
 * and its database.
 * Afterwards, the stream (FILE) of the
 * connection is opened through calling
 * of function fopen, either in 
 * reading mode (for flag <mode>="c")
 * or in reading and writing mode
 * (for all other modes)
 * Afterwards, the database of the 
 * new connection is loaded
 *
 *****************************************/ 
struct Connection *Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn)
    die("Memory Error!\n");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die("Memory Error!\n");

  if (mode == 'c'){
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file){
      Database_load(conn);
    }
  }

  if (!conn->file)
    die("Failed to open the file.\n");

  return conn;

}


/******************************************
 * Function: Database_close
 * ----------------------------------------
 * Closes the database and frees its 
 * memory and closes its stream to the
 * stream
 *
 *****************************************/ 
void Database_close(struct Connection *conn)
{
  if (conn){
    if (conn->file)
      fclose(conn->file);
    if (conn->db)
      free(conn->db);
    free(conn);
  }
}


/******************************************
 * Function: Database_write
 * ----------------------------------------
 * Writes data to the database file
 *
 *****************************************/ 
void Database_write(struct Connection *conn)
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc!=1)
    die("Failed to write database.\n");

  rc = fflush(conn->file);
  if (rc==-1)
    die("Cannot flush database.\n");
}

/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
void Database_create(struct Connection *conn)
{
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++){
    // make a prototype to initialize it
    struct Address addr = {.id = i, .set = 0 };
    // then just assign it
    conn->db->rows[i] = addr;
  }
}

/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
void Database_set(struct Connection *conn, int id, const char *name,
                  const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Already set, delete it first.\n");

  addr->set = 1;
  // WARNING BUG: read the how to break it and fix it!
  char *res = strncpy(addr->name, name, MAX_DATA);
  // demonstrate the strncpy bug
  if (!res)
    die("Name copy failed.\n");

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res)
    die("Email copy failed.\n");
}


/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set){
    Address_print(addr);
  } else {
    die("ID not set.\n");
  }
}


/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
void Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}


/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i<MAX_ROWS; i++){
    struct Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}



/******************************************
 * Function: 
 * ----------------------------------------
 * 
 *****************************************/ 
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Action:\n\tc - create\n");
    printf("\tg - get\n");
    printf("\ts - set\n");
    printf("\tl - list\n");
    printf("\td - delete\n");
    die("USAGE: ex17 <dbfile> <action> [action params]");
  }

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int id = 0;

  if (argc > 3)
    id = atoi(argv[3]);

  if (id > MAX_ROWS)
    die("There's not that many records.\n");

  switch (action) {
    
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if (argc != 4)
        die("Need an ID to get.\n");

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6)
        die("Need ID, Name, Email to set.\n");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if (argc != 4)
        die("Need ID to delete.\n");

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      printf("---|----------------------------------------------------|\n");
      Database_list(conn);
      printf("---|----------------------------------------------------|\n");
      break;

    default:
      die("Invalid action: c=create, g=get, s=set, d=del, l=list \n");
  
  }

  Database_close(conn);


  return 0;

}
