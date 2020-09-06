#include "ast.h"
#include "grammar.h"
struct node_simple *init_simple_cmd(struct node_prefix *pref, struct node_element *elt)
{
	struct node_simple *new = malloc(sizeof(struct node_simple));
	new->prefix = pref;
	new->element = elt;
	new->next = NULL;
	return new;
}

struct node_simple *rule_simple_command()
{
	struct node_simple *simple_cmd = NULL;
	struct node_prefix *pref = rule_prefix();
	if (pref)
	{	
		simple_cmd = init_simple_cmd(pref, NULL);
		struct node_prefix *prefix = rule_prefix();
		if (prefix)
		{
			struct node_simple *next = init_simple_cmd(prefix, NULL);
			simple_cmd->next = next;			
		}
		return simple_cmd;
	}

	struct node_element *elt = rule_element();
	if (elt)
	{
		simple_cmd = init_simple_cmd(NULL, elt);
		
		struct node_element *element = rule_element();
		struct node_simple *tmp = simple_cmd;
		while (element)
		{
			struct node_simple *next = init_simple_cmd(NULL, element);
			tmp->next = next;
			tmp = tmp->next;
			element = rule_element();
		}
		return simple_cmd;
	}
	else
		return NULL;
}
