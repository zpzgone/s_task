/* Copyright xhawk, MIT license */

/* Timer functions need to be implemented on a new porting. */

static uv_loop_t* s_task_uv_loop(void);
static uv_timer_t* s_task_uv_timer(void);

void my_clock_init(){
    uv_loop_t* loop = s_task_uv_loop();
    uv_timer_init(loop, s_task_uv_timer());
}

my_clock_t my_clock() {
	uv_loop_t* loop = s_task_uv_loop();
	return uv_now(loop);
}

static void uv_on_timer(uv_timer_t* handle) {
    //uv_close((uv_handle_t*)handle, NULL);
}

void my_on_idle(uint64_t max_idle_ms) {
    uv_timer_start(s_task_uv_timer(), uv_on_timer, max_idle_ms, 0);
}


#if (defined(i386) || defined(__i386__) || defined(__i386) \
     || defined(__i486__) || defined(__i586__) || defined(__i686__) \
     || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) \
     || defined(__I86__) || defined(__INTEL__) || defined(__IA32__) \
     || defined(_M_IX86) || defined(_I86_)) && defined(_WIN32)
# define BOOST_CONTEXT_CALLDECL __cdecl
#else
# define BOOST_CONTEXT_CALLDECL
#endif

extern
transfer_t BOOST_CONTEXT_CALLDECL jump_fcontext( fcontext_t const to, void * vp);
extern
fcontext_t BOOST_CONTEXT_CALLDECL make_fcontext( void * sp, size_t size, void (* fn)( transfer_t) );


void create_fcontext(fcontext_t *fc, void * sp, size_t size, void (* fn)( transfer_t)) {
	sp = (void *)((char *)sp + size);
	*fc = make_fcontext(sp, size, fn);
}
