#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

/*

  A hash table is a data structure that is loosely based on lists. A hash table is often used
  to implement dictionaries (e.g. in Python).

  Consider a simple application: store and retrieve some words (strings). A simple way is to store
  them in a singly linked list, like this:

  "fox" -> "jump" -> "mare" -> "amit" -> "happy" -> "sad" -> "smile" -|


  To insert a new word, we can simply insert it at the end (or beginning).

  Now we wish to find if the word "smile" exists in this list. Our only choice is to go through this
  list one by one, and we find it only at the end. The word "frown" is not present in the list, but
  can know this only after going through the whole list. This works correctly, but as you can imagine,
  can be very slow! (Imagine such a list of all the contacts in your phone, or friends on social media.  Now imagine trying to find if a given name is in your contacts/friends list or not!)

  Intuitively, it would be nice if we somehow knew to start not at the beginning, but somewhere
  in the middle. Effectively, we would be able to skip some elements and thus find (or fail) sooner.

  One way is to break down the above list alphabetically, like our phone contact list does. We
  maintain a separate list for each letter:

  a -> "amit"
  b -> empty
  ...
  f -> "fox"
  ...
  s -> "sad" -> "smile"


  Now if we wish to find "smile", we can go directly to the "s" list, skipping all the words that
  start with a letter before "s". Now we only go through one word before finding it! Similarly, if
  we wish to find "frown", we go directly to the "f" list, go through one word and conclude that
  "frown" is not present anywhere because it is not there in the "f" list. Much quicker!

  How do we organize this? This is a "list of lists", or more specifically, an "array of lists".
  Given a word, we wish to find which list to look through, based on the first letter of the word.

  We can do this simply, as follows:

  int foo(char *name) {
    int a_code = (int)'a';
    return ((int)name[0] - a_code);
  }

  The above function will return us "how far" away from 'a' we are. We assume here that all names
  are lowercase.

  Thus, adding a name to our contact list is simple:

  add(contacts,name) {
    int index;

    index = foo(name);
    //add "name" to the list at contacts[index]
  }

  Similarly, look up a name?

  is_a_friend(contacts,name) {
    int index;

    index = foo(name);
    //if "name" is present in the list contacts[index] return true, else return false
  }

  "contacts" above is an array of lists. More specifically, it is an array of "head pointers"!
  No matter how many names we have to add, we know the size of this array: 26!
  
  This simple scheme has a limitation though: what if we know 20 people whose names start with 'a'
  but only 2 whose names that start with 'z'? We can see that this way of organizing the names,
  although better than the first, can still result in pretty long lists.

  So we keep the same concept, but change that "foo" function a bit: instead of merely looking at
  the first letter, we look at the first, and the last:

  int foo(char *name) {
    int size = strlen(name);
    char first = name[0];
    char last = name[size-1];
    int a_code = (int)'a';

    int index = ((int)first + (int)last)/2 - a_code;

    return index;
  }

  Note that index will still be between 0 and 25 (both included). 

  In fact, we can make the foo function more complicated, so long as the number it returns is
  between 0 and 25 (i.e. a valid index for our contacts list)

  int foo(char *name) {
    int index = do-whatever-math-you-want;

    index = index % 26; //this ensures that index is now between 0 and 25
    return index;
  }

  The crucial thing is that given a name to add (or look for), we "pass it " through the same function
  and use its result to look up the contacts list.

  -------

  What we have just discovered is a data structure: this is called a "hash table".

  The hash table is particularly good at quickly at finding things. Hash tables are very popular,
  and they can get complicated, but the above concept remains. A hash table is simply:

  1. A list-like organization, most commonly an array of something.
  2. A function that tells us where to go look (to insert, or to find). This is our "foo" function.

  Note what this function must do:

  1. It must take as input the thing you wish to insert or find (in our case, the name)
  2. It must know the size of the underlying list (in our case, 26. But it can take this as a parameter).
  3. It must return an integer that is between 0 and size-1.

  Such a function is called a "hash function". This function can be anything you want, so long as it
  has the above three properties. Of course we would like this function to do its job quickly.

  So, a few terms to summarize:

  The function above = "hash function"
  (array, hash function) = "hash table"
  each element of the array = "bucket"
  size of the array = "number of buckets"

  Below you must implement such a hash table that stores strings.
  

 */

#include <stdbool.h>

//each node inside the bucket. Remember that each bucket here is a singly linked list.

typedef struct node {
  char *data;
  struct node *next;
} node_t;

//"hashfunction_type" represents a pointer to a function that takes in a char * and an int, and
//returns an int
typedef int (*hashfunction_type)(char *,int);

/*

  What? A pointer to ...a function?

  Yes! Remember that functions are just instructions, which have to be stored in memory too.
  This pointer just points to the first line of that function.

  Unlike other pointers that you use to put and get data, this pointer can only be used to call
  the function it is pointing to.

  Here is an example:

  int foo(char *name,int buckets) {
    ...
  }

  hashfunction_type somefunc;

  somefunc = foo; //somefunc now "points to" foo.

  foo("amit",5); //call foo normally

  somefunc("amit",5); //call foo through the function pointer!

  You can also do crazy things like:

  hashfunction_type somefuncs[] = {foo,otherfoo,someotherfoo};

  where all of these functions take in a char * and an int, and return an int. Now...

  for (int i=0;i<3;i+=1) {
    somefuncs[i]("amit",5"); //call all of them, one-by-one
  }

  Think about how this can make your test suite easier to write!

 */

//our hash table 

typedef struct hashtable {
  node_t ** buckets;
  int no_of_buckets; 

  hashfunction_type hash_function;
} hashtable_t;


//create and return an empty hash table that has the specified number of buckets. It must have the
//hash function pointer initialized properly.
/*

  When you implement this function in hashtable.c, you must write a hash function that takes
  the average of the first, last and middle (character at size/2) characters of the string, modulo the number of buckets.
  No need to subtract 'a', because the modulo takes care of ensuring a valid index is returned.

  If the string passed to it is empty, return 0

 */
hashtable_t *create_hashtable(int buckets);

//add the specified "entry" into the given hash table, using the hash function inside the table. Read above to see what you must do.

//this function adds the entry into the hash table only if it does not already exist.
void hashtable_add(hashtable_t *table,char *entry);

//return true if the given entry is present in the given table, false otherwise. This must use the
//hash function inside the table
bool hashtable_contains(hashtable_t *table,char *entry);

//delete this hash table. This includes all its entry, and the table itself!
void delete_hashtable(hashtable_t *table);


#endif
