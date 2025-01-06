#ifndef KOLIBRI_LIBINI_H
#define KOLIBRI_LIBINI_H

#include <stdint.h>

extern int kolibri_libini_init(void);

typedef void (*LIBINI_enumSetionsFunc)(const char *f_name, const char *sec_name);
typedef void (*LIBINI_enumKeysFunc)(const char *f_name, const char *sec_name, const char *key_name, const char *key_value);

/*
 * Enumerate sections, calling callback function for each of them.
 */
extern uint32_t (*LIBINI_enum_sections)(const char *f_name, LIBINI_enumSetionsFunc func) __attribute__((__stdcall__));

/*
 * Enumerate keys within a section, calling callback function for each of them.
 */
extern uint32_t (*LIBINI_enum_keys)(const char *f_name, const char *sec_name, LIBINI_enumKeysFunc func) __attribute__((__stdcall__));

/*
 * Read string.
 */
extern uint32_t (*LIBINI_get_str)(const char *f_name, const char *sec_name, const char *key_name, char *buffer, uint32_t buf_len) __attribute__((__stdcall__));

/*
 * Write string.
 */
extern uint32_t (*LIBINI_set_str)(const char *f_name, const char *sec_name, const char *key_name, const char *buffer, uint32_t buf_len) __attribute__((__stdcall__));

/*
 * Read integer.
 */
extern uint32_t (*LIBINI_get_int)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val) __attribute__((__stdcall__));

/*
 * Write integer.
 */
extern uint32_t (*LIBINI_set_int)(const char *f_name, const char *sec_name, const char *key_name, uint32_t val) __attribute__((__stdcall__));

/*
 * Read color.
 */
extern uint32_t (*LIBINI_get_color)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val) __attribute__((__stdcall__));

/*
 * Write color.
 */
extern uint32_t (*LIBINI_set_color)(const char *f_name, const char *sec_name, const char *key_name, uint32_t val) __attribute__((__stdcall__));

/*
 * Read shortcut key.
 */
extern uint32_t (*LIBINI_get_shortcut)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val, uint32_t *modifiers) __attribute__((__stdcall__));

/*
 * Delete section
 * Delete section and all key in this section
 */
extern uint32_t (*LIBINI_del_section)(const char *f_name, const char *sec_name) __attribute__((__stdcall__));

#endif /* KOLIBRI_LIBINI_H */
