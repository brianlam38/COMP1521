// String is NOT defined inside the struct.
typedef struct _node1 Node1;
struct _node1 {
	char *str;		// pointer to string
	Node1 *next;
}

// String is defined inside the struct
typedef struct _node2 Node2;
struct _node2 {
	char str[5];	// string defined inside struct
	Node2 *next;
}

// create new node with its own copy of string
Node1 *makeNode1(char *s)
{
	Node *new;
	new = malloc(sizeof(Node1));
	//new->string = strdup(s);			METHOD 1: strdup() = makes a copy of string passed in, so that
	//   											 		when the function somewhere that passes in
	//														*s stops, it won't destroy data in the struct.

	char *news = malloc(strlen(s)+1);  	 // METHOD 2: malloc size of string + 1 for null byte
	for (int i = 0; s[i] != '\0'; i++) { //			  copy each char across
		news[i] = s[i];					 //			  set last char = null byte
	}
	news[i] = '\0';
	new->next = NULL;	
	return new;		 
}								

// create new node with its own copy of string
Node2 *makeNode2(char *s)
{
	Node2 *new;
	new = malloc(sizeof(Node2));
	//strlcpy(new->s, s);			METHOD 1: strlcpy null terminates the copied string automatically
	strcpy(new->str, s, 4);		 // METHOD 2: strcpy + define size of string + manually add null-byte
	s[4] = '\0';
	new->next  = NULL;
	return new;
}
