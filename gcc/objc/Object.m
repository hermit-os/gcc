/* The implementation of class Object for Objective-C.
   Copyright (C) 1993 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU CC is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, if you link this library with files compiled
   with GCC to produce an executable, this does not cause the resulting
   executable to be covered by the GNU General Public License.  This
   exception does not however invalidate any other reasons why the
   executable file might be covered by the GNU General Public License. */

#include "objc/Object.h"
#include "objc/Protocol.h"
#include "objc/objc-api.h"

extern int errno;

#define MAX_CLASS_NAME_LEN 256

@implementation Object

+ initialize
{
  return self;
}

- init
{
  return self;
}

+ new
{
  return [[self alloc] init];
}

+ alloc
{
  return class_create_instance(self);
}

- free
{
  return object_dispose(self);
}

- copy
{
  return [[self shallowCopy] deepen];
}

- shallowCopy
{
  return object_copy(self);
}

- deepen
{
  return self;
}

- deepCopy
{
  return [self copy];
}

- (Class_t)class
{
  return object_get_class(self);
}

- (Class_t)superClass
{
  return object_get_super_class(self);
}

- (MetaClass_t)metaClass
{
  return object_get_meta_class(self);
}

- (const char *)name
{
  return object_get_class_name(self);
}

- self
{
  return self;
}

- (unsigned int)hash
{
  return (size_t)self;
}

- (BOOL)isEqual:anObject
{
  return self==anObject;
}

- (BOOL)isMetaClass
{
  return NO;
}

- (BOOL)isClass
{
  return object_is_class(self);
}

- (BOOL)isInstance
{
  return object_is_instance(self);
}

- (BOOL)isKindOf:(Class_t)aClassObject
{
  Class_t class;

  for (class = self->isa; class!=Nil; class = class_get_super_class(class))
    if (class==aClassObject)
      return YES;
  return NO;
}

- (BOOL)isMemberOf:(Class_t)aClassObject
{
  return self->isa==aClassObject;
}

- (BOOL)isKindOfClassNamed:(const char *)aClassName
{
  Class_t class;

  if (aClassName!=NULL)
    for (class = self->isa; class!=Nil; class = class_get_super_class(class))
      if (!strcmp(class_get_class_name(class), aClassName))
        return YES;
  return NO;
}

- (BOOL)isMemberOfClassNamed:(const char *)aClassName
{
  return ((aClassName!=NULL)
          &&!strcmp(class_get_class_name(self->isa), aClassName));
}

+ (BOOL)instancesRespondTo:(SEL)aSel
{
  return class_get_instance_method(self, aSel)!=METHOD_NULL;
}

- (BOOL)respondsTo:(SEL)aSel
{
  return ((object_is_instance(self)
           ?class_get_instance_method(self->isa, aSel)
           :class_get_class_method(self->isa, aSel))!=METHOD_NULL);
}

+ (IMP)instanceMethodFor:(SEL)aSel
{
  return method_get_imp(class_get_instance_method(self, aSel));
}

// Indicates if the receiving class or instance conforms to the given protocol
// not usually overridden by subclasses
- (BOOL) conformsTo: (Protocol*)aProtocol
{
  int i;
  struct objc_protocol_list* proto_list;

  for (proto_list = isa->protocols;
       proto_list; proto_list = proto_list->next)
    {
      for (i=0; i < proto_list->count; i++)
      {
        if ([proto_list->list[i] conformsTo: aProtocol])
          return YES;
      }
    }

  return NO;
}

- (IMP)methodFor:(SEL)aSel
{
  return (method_get_imp(object_is_instance(self)
                         ?class_get_instance_method(self->isa, aSel)
                         :class_get_class_method(self->isa, aSel)));
}

+ (struct objc_method_description *)descriptionForInstanceMethod:(SEL)aSel
{
  return ((struct objc_method_description *)
           class_get_instance_method(self, aSel));
}

- (struct objc_method_description *)descriptionForMethod:(SEL)aSel
{
  return ((struct objc_method_description *)
           (object_is_instance(self)
            ?class_get_instance_method(self->isa, aSel)
            :class_get_class_method(self->isa, aSel)));
}

- perform:(SEL)aSel
{
  IMP msg = objc_msg_lookup(self, aSel);
  if (!msg)
    return [self error:"invalid selector passed to %s", sel_get_name(_cmd)];
  return (*msg)(self, aSel);
}

- perform:(SEL)aSel with:anObject
{
  IMP msg = objc_msg_lookup(self, aSel);
  if (!msg)
    return [self error:"invalid selector passed to %s", sel_get_name(_cmd)];
  return (*msg)(self, aSel, anObject);
}

- perform:(SEL)aSel with:anObject1 with:anObject2
{
  IMP msg = objc_msg_lookup(self, aSel);
  if (!msg)
    return [self error:"invalid selector passed to %s", sel_get_name(_cmd)];
  return (*msg)(self, aSel, anObject1, anObject2);
}

- forward:(SEL)aSel :(arglist_t)argFrame
{
  return [self doesNotRecognize: aSel];
}

- performv:(SEL)aSel :(arglist_t)argFrame
{
  return objc_msg_sendv(self, aSel, method_get_argsize(0), argFrame);
}

+ poseAs:(Class_t)aClassObject
{
  return class_pose_as(self, aClassObject);
}

- (Class_t)transmuteClassTo:(Class_t)aClassObject
{
  if (object_is_instance(self))
    if (class_is_class(aClassObject))
      if (class_get_instance_size(aClassObject)==class_get_instance_size(isa))
        if ([self isKindOf:aClassObject])
          {
            Class_t old_isa = isa;
            isa = aClassObject;
            return old_isa;
          }
  return nil;
}

- subclassResponsibility:(SEL)aSel
{
  return [self error:"subclass should override %s", sel_get_name(aSel)];
}

- notImplemented:(SEL)aSel
{
  return [self error:"method %s not implemented", sel_get_name(aSel)];
}

- doesNotRecognize:(SEL)aSel
{
  return [self error:"%s does not recognize %s",
                     object_get_class_name(self), sel_get_name(aSel)];
}

- error:(const char *)aString, ...
{
#define FMT "error: %s (%s)\n%s\n"
  char fmt[(strlen((char*)FMT)+strlen((char*)object_get_class_name(self))
            +((aString!=NULL)?strlen((char*)aString):0)+8)];
  va_list ap;

  sprintf(fmt, FMT, object_get_class_name(self),
                    object_is_instance(self)?"instance":"class",
                    (aString!=NULL)?aString:"");
  va_start(ap, aString);
  (*_objc_error)(self, fmt, ap);
  va_end(ap);
  return nil;
#undef FMT
}

+ (int)version
{
  return class_get_version(self);
}

+ setVersion:(int)aVersion
{
  class_set_version(self, aVersion);
  return self;
}

+ (int)streamVersion: (TypedStream*)aStream
{
#ifndef __alpha__
  if (aStream->mode == OBJC_READONLY)
    return objc_get_stream_class_version (aStream, self);
  else
#endif
    return class_get_version (self);
}

// These are used to write or read the instance variables 
// declared in this particular part of the object.  Subclasses
// should extend these, by calling [super read/write: aStream]
// before doing their own archiving.  These methods are private, in
// the sense that they should only be called from subclasses.

- read: (TypedStream*)aStream
{
  // [super read: aStream];  
  return self;
}

- write: (TypedStream*)aStream
{
  // [super write: aStream];
  return self;
}

- awake
{
  // [super awake];
  return self;
}

@end
