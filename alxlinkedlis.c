#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end -Adds Node alias.
 * @head:A pointer of the list_t list.
 * @name:The Name of the new alias to be added.
 * @value:The value of the new alias to be added.
 *
 * Return:NULL.
 *         A pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *node = malloc(sizeof(alias_t));
	alias_t *l;

	if (!node)
		return (NULL);

	node->next = NULL;
	node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!node->name)
	{
		free(nnode);
		return (NULL);
	}
	node->value = value;
	_strcpy(node->name, name);

	if (*head)
	{
		l = *head;
		while (l->next != NULL)
			l = l->next;
		l->next = node;
	}
	else
		*head = node;

	return (node);
}

/**
 * add_node_end - -Adds Node linked.
 * @head: A pointer of the list_t list.
 * @dir: The directory path for the new_node.
 *
 * Return: NULL.
 *         Node.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *l;

	if (!node)
		return (NULL);

	node->dir = dir;
	node->next = NULL;

	if (*head)
	{
		l = *head;
		while (l->next != NULL)
			l = l->next;
		l->next = node;
	}
	else
		*head = node;

	return (node);
}

/**
 * free_alias_list -Free.
 * @head:alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *nx;

	while (head)
	{
		nx = head->nx;
		free(head->name);
		free(head->value);
		free(head);
		head = nx;
	}
}

/**
 * free_list-Free.
 * @head:The list_t list.
 */
void free_list(list_t *head)
{
	list_t *nx;

	while (head)
	{
		nx = head->nx;
		free(head->dir);
		free(head);
		head = nx;
	}
}
