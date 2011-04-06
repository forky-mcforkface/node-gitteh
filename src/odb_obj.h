#ifndef GITTEH_ODB_OBJ_H
#define GITTEH_ODB_OBJ_H

#include "gitteh.h"
#include "gitobjectwrap_new.h"

namespace gitteh {

class ObjectDatabase;
struct init_data;

class ODBObject : public WrappedGitObject<ObjectDatabase, ODBObject, git_odb_object> {
public:
	static Persistent<FunctionTemplate> constructor_template;

	static void Init(Handle<Object>);
	static Handle<Value> SaveObject(Handle<Object>, ObjectDatabase*, Handle<Value>, bool);

	ODBObject(git_odb_object*);
	~ODBObject();
	void setOwner(ObjectDatabase*);

protected:
	static Handle<Value> New(const Arguments&);
	static Handle<Value> Save(const Arguments&);

	int doInit();

private:
	void processInitData();

	static int EIO_Save(eio_req*);
	static int EIO_AfterSave(eio_req*);

	ObjectDatabase *odb_;
	git_odb_object *obj_;
	init_data *initData_;
};

} // namespace gitteh

#endif //GITTEH_ODB_OBJ_H