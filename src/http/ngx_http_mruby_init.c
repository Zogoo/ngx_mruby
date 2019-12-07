/*
// ngx_http_mruby_init.c - ngx_mruby mruby init functions
//
// See Copyright Notice in ngx_http_mruby_module.c
*/

#include "ngx_http_mruby_init.h"

#include "ngx_http_mruby_async.h"
#include "ngx_http_mruby_connection.h"
#include "ngx_http_mruby_core.h"
#include "ngx_http_mruby_filter.h"
#include "ngx_http_mruby_request.h"
#include "ngx_http_mruby_ssl.h"
#include "ngx_http_mruby_server.h"
#include "ngx_http_mruby_upstream.h"
#include "ngx_http_mruby_var.h"

#include <mruby.h>
#include <mruby/compile.h>

#define GC_ARENA_RESTORE mrb_gc_arena_restore(mrb, 0);

ngx_int_t ngx_mrb_class_init(mrb_state *mrb)
{
  struct RClass *class;

  class = mrb_define_class(mrb, "Nginx", mrb->object_class);

  ngx_mrb_core_class_init(mrb, class);
  GC_ARENA_RESTORE;
  ngx_mrb_request_class_init(mrb, class);
  GC_ARENA_RESTORE;
  ngx_mrb_var_class_init(mrb, class);
  GC_ARENA_RESTORE;
  ngx_mrb_conn_class_init(mrb, class);
  GC_ARENA_RESTORE;
  ngx_mrb_server_class_init(mrb, class);
  GC_ARENA_RESTORE;
  ngx_mrb_filter_class_init(mrb, class);
  GC_ARENA_RESTORE;
#ifdef NGX_USE_MRUBY_UPSTREAM
  ngx_mrb_upstream_class_init(mrb, class);
  GC_ARENA_RESTORE;
#endif
#if (NGX_HTTP_SSL)
  ngx_mrb_ssl_class_init(mrb, class);
  GC_ARENA_RESTORE;
#endif
  ngx_mrb_async_class_init(mrb, class);
  GC_ARENA_RESTORE;

  return NGX_OK;
}
