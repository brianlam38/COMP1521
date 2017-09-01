// String is NOT defined inside the struct.
typedef struct _node1 Node1;
struct _node1 {
	char *str;		// pointer to string
	Node *next;
}

// String is defined inside the struct
typedef struct _node2 Node2;
struct _node2 {
	char str[5];	// string defined inside struct
	Node *next;
}

// create new node with its own copy of string
Node1 *makeNode1(char *s)
{
	Node *new;
	new = malloc(sizeof(Node1));
	new->string = strdup(s);	// strdup() = makes a copy of string passed in, so that
	new->next = NULL;			//			  when the function somewhere that passes in
}								//			  *s stops, it won't destroy data in the struct.

// create new node with its own copy of string
Node2 *makeNode2(char *str)
{
}
