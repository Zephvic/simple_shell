#include "shell.h"

/**
 * _myenvi - prints the current environment
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myenvi(info_t *info)
{
	print_list_str(info->envi);
	return (0);
}

/**
 * _getenviron - function that gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenviron(info_t *info, const char *name)
{
	list_t *node = info->environ;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mynewenv - function that Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _mynewenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _remove_env - function that remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _remove_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
