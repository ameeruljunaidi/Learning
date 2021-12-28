# Data Structures

## Creating A Linked List

1. Create an empty node called list, this is going to be the head of our linked list

```c
node *list = NULL;
```

2. Create a new node, allocate space using malloc

```c
node *n = malloc(sizeof(node));
if (n == NULL)
{
  return 1;
}
n->number = 1; // Assigning (*n).number = 1;
n->next = NULL; // Assigning (*n).next = NULL since it does not yet have a next
list = n; // Chaning the pointer list to point to pointer n instead
```

3. Adding a new number to the linked list

```c
n = malloc(sizeof(node)); // Allocate a new space in memory with the size of node
if (n == NULL)
{
  return 1;
}
n->number = 3;
n->next = NULL;
list->next = n;
```

Explanation on last line: 

Recall that `list` is also a node with the attributes `number` and `next`. Before (in step 2), `list`'s next was NULL but now we have to connect it to n, which is what we are adding to the linked list.

4. Adding another new number to the liked list

```c
n = malloc(sizeof(node));
if (n == NULL)
{
	return 1;
}
n->number = 5;
n->next = NULL;
list->next->next = n;
```

Similar to last time, since we are following the path right from the head of the list, we need to direct the node through the previous nodes using `->next->next`.

5. Printing the linkedin list

This is a good opportunity to see how a loop is going to look very different to an array.

- Create a temp node (`tmp`) and point it to the list
- Keep doing (the following) so long as `tmp != NULL`
- Update the `tmp` pointer to be whatever the next pointer is

```c
for (node *tmp = list; tmp != NULL; tmp = tmp-> next)
{
  printf("%i\n", tmp->number);
}
```

6. Freeing the list (need to do this since we allocated the memory using malloc)

When freeing the whole list, need to free all the mallocs that we have called. Since we have malloc'ed three times, then we need to free it three times. However, to get to the pointers for those nodes, we need to follow the link between those nodes. 

```c
while (list != NULL)
{
  node *tmp = list-> next;
  free(list);
  list = tmp;
}
```

We are essentially freeing the last node first. We can find the last node, if it is `NULL`, hence why we use the loop condition `while (list != NULL)`. 

> Why are we not freeing `tmp`? Why are we freeing `list`? If we're freeing `list` doesn't that mean we're losing all the subsequent nodes?

Something in the tree.c example makes more sense. It does it recursively.

```c
void free_tree(node *root)
{
  if (root == NULL)
  {
    return;
  }
  free_tree(root->left);
  free_tree(root>right);
  free(root);
}
```

