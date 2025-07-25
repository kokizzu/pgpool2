/*-------------------------------------------------------------------------
 *
 * extensible.h
 *	  Definitions for extensible nodes and custom scans
 *
 *
 * Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/nodes/extensible.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef EXTENSIBLE_H
#define EXTENSIBLE_H

/* maximum length of an extensible node identifier */
#define EXTNODENAME_MAX_LEN					64

/*
 * An extensible node is a new type of node defined by an extension.  The
 * type is always T_ExtensibleNode, while the extnodename identifies the
 * specific type of node.  extnodename can be looked up to find the
 * ExtensibleNodeMethods for this node type.
 */
typedef struct ExtensibleNode
{
	NodeTag		type;
	const char *extnodename;	/* identifier of ExtensibleNodeMethods */
}			ExtensibleNode;

/*
 * node_size is the size of an extensible node of this type in bytes.
 *
 * nodeCopy is a function which performs a deep copy from oldnode to newnode.
 * It does not need to copy type or extnodename, which are copied by the
 * core system.
 *
 * nodeEqual is a function which performs a deep equality comparison between
 * a and b and returns true or false accordingly.  It does not need to compare
 * type or extnodename, which are compared by the core system.
 *
 * nodeOut is a serialization function for the node type.  It should use the
 * output conventions typical for outfuncs.c.  It does not need to output
 * type or extnodename; the core system handles those.
 *
 * nodeRead is a deserialization function for the node type.  It does not need
 * to read type or extnodename; the core system handles those.  It should fetch
 * the next token using pg_strtok() from the current input stream, and then
 * reconstruct the private fields according to the manner in readfuncs.c.
 *
 * All callbacks are mandatory.
 */
typedef struct ExtensibleNodeMethods
{
	const char *extnodename;
	Size		node_size;
	void		(*nodeCopy) (struct ExtensibleNode *newnode,
							 const struct ExtensibleNode *oldnode);
	bool		(*nodeEqual) (const struct ExtensibleNode *a,
							  const struct ExtensibleNode *b);
	void		(*nodeOut) (struct StringInfoData *str,
							const struct ExtensibleNode *node);
	void		(*nodeRead) (struct ExtensibleNode *node);
}			ExtensibleNodeMethods;

extern void RegisterExtensibleNodeMethods(const ExtensibleNodeMethods * method);
extern const ExtensibleNodeMethods *GetExtensibleNodeMethods(const char *name,
															 bool missing_ok);

/*
 * Flags for custom paths, indicating what capabilities the resulting scan
 * will have.
 */
#define CUSTOMPATH_SUPPORT_BACKWARD_SCAN	0x0001
#define CUSTOMPATH_SUPPORT_MARK_RESTORE		0x0002

#endif							/* EXTENSIBLE_H */
