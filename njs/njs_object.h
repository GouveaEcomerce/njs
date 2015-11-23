
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) NGINX, Inc.
 */

#ifndef _NJS_OBJECT_H_INCLUDED_
#define _NJS_OBJECT_H_INCLUDED_


struct njs_object_s {
    /* A private hash of njs_object_prop_t. */
    nxt_lvlhsh_t                hash;

    /* A shared hash of njs_object_prop_t. */
    nxt_lvlhsh_t                shared_hash;

    /* An object __proto__. */
    njs_object_t                *__proto__;
};


struct njs_object_value_s {
    njs_object_t                object;
    njs_value_t                 value;
};


typedef enum {
    NJS_PROPERTY = 0,
    NJS_GETTER,
    NJS_SETTER,
    NJS_METHOD,
    NJS_NATIVE_GETTER,
    NJS_NATIVE_SETTER,
    NJS_WHITEOUT,
} njs_object_property_type_t;


typedef struct {
    /* Must be aligned to njs_value_t. */
    njs_value_t                 value;
    njs_value_t                 name;

    njs_object_property_type_t  type:8;        /* 3 bits */
    uint8_t                     enumerable;    /* 1 bit  */
    uint8_t                     writable;      /* 1 bit  */
    uint8_t                     configurable;  /* 1 bit  */
} njs_object_prop_t;


njs_object_t *njs_object_alloc(njs_vm_t *vm);
njs_object_t *njs_object_value_alloc(njs_vm_t *vm, const njs_value_t *value,
    nxt_uint_t prototype);
njs_ret_t njs_object_method(njs_vm_t *vm, njs_param_t *param,
    nxt_lvlhsh_query_t *lhq);
njs_object_prop_t *njs_object_property(njs_vm_t *vm, njs_object_t *obj,
    nxt_lvlhsh_query_t *lhq);
nxt_int_t njs_object_hash_create(njs_vm_t *vm, nxt_lvlhsh_t *hash,
    const njs_object_prop_t *prop, nxt_uint_t n);
njs_ret_t njs_object_function(njs_vm_t *vm, njs_param_t *param);
njs_object_prop_t *njs_object_prop_alloc(njs_vm_t *vm, const njs_value_t *name);
njs_ret_t njs_primitive_prototype_get_proto(njs_vm_t *vm, njs_value_t *value);
njs_ret_t njs_object_prototype_create_prototype(njs_vm_t *vm,
    njs_value_t *value);
nxt_int_t njs_object_function_hash(njs_vm_t *vm, nxt_lvlhsh_t *hash);
nxt_int_t njs_object_prototype_hash(njs_vm_t *vm, nxt_lvlhsh_t *hash);


#endif /* _NJS_OBJECT_H_INCLUDED_ */
