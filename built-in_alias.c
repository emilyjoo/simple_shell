#include "shell.h"

int alias_cmd(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * set_alias - sets an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, i, j;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, i = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[i++] = value[j];
	}
	new_value[i] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}
/**
 * replace_aliases - replaces any matching alias with their value.
 * @args: a 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int j;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (j = 0; args[j]; j++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[j], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[j]);
				args[j] = new_value;
				j--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
/**
 * alias_cmd  - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of args
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alias_cmd(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int j, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (j = 0; args[j]; j++)
	{
		temp = aliases;
		value = _strchr(args[j], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[j], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + j, 1);
		}
		else
			set_alias(args[j], value);
	}
	return (ret);
}
/**
 * print_alias - displays the alias in the format name='value'
 * @alias: Pointer to an alias
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
