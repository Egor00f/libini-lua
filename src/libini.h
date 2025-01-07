#ifndef KOLIBRI_LIBINI_H
#define KOLIBRI_LIBINI_H

#include <stdint.h>
#include <sys/ksys.h>

#define LIBS_PATH "/sys/lib"
#define LIBINI_NAME "libini.obj"
#define LIBINI_FULLNAME LIBS_PATH "/" LIBINI_NAME

typedef void (*LIBINI_enumSectionsFunc)(const char *f_name, const char *sec_name);

typedef void (*LIBINI_enumKeysFunc)(const char *f_name, const char *sec_name, const char *key_name, const char *key_value);

/*
 * Enumerate sections, calling callback function for each of them.
 */
uint32_t (*LIBINI_enum_sections)(const char *f_name, LIBINI_enumSectionsFunc func);

/*
 * Enumerate keys within a section, calling callback function for each of them.
 */
uint32_t (*LIBINI_enum_keys)(const char *f_name, const char *sec_name, LIBINI_enumKeysFunc func);

/*
 * Read string.
 */
uint32_t (*LIBINI_get_str)(const char *f_name, const char *sec_name, const char *key_name, char *buffer, uint32_t buf_len);

/*
 * Write string.
 */
uint32_t (*LIBINI_set_str)(const char *f_name, const char *sec_name, const char *key_name, const char *buffer, uint32_t buf_len);

/*
 * Read integer.
 */
uint32_t (*LIBINI_get_int)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val);

/*
 * Write integer.
 */
uint32_t (*LIBINI_set_int)(const char *f_name, const char *sec_name, const char *key_name, uint32_t val);

/*
 * Read color.
 */
uint32_t (*LIBINI_get_color)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val);

/*
 * Write color.
 */
uint32_t (*LIBINI_set_color)(const char *f_name, const char *sec_name, const char *key_name, uint32_t val);

/*
 * Read shortcut key.
 */
uint32_t (*LIBINI_get_shortcut)(const char *f_name, const char *sec_name, const char *key_name, uint32_t def_val, uint32_t *modifiers);

/*
 * Delete section
 * Delete section and all key in this section
 */
uint32_t (*LIBINI_del_section)(const char *f_name, const char *sec_name);

/*
 * Loaded library
 */
static ksys_dll_t *libini = NULL;

/*
 * Load libini
 */
int kolibri_libini_init(void);

/*
 * Close libini
 */
int kolibri_libini_close();

#endif /* KOLIBRI_LIBINI_H */
