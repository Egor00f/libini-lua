#include "libini.h"

int kolibri_libini_init(void)
{
#ifdef NDEBUG
	_ksys_debug_puts("libini load: ");
#endif
	libini = _ksys_dlopen(LIBINI_FULLNAME);

	if (libini != NULL) // if lib loaded
	{
		LIBINI_enum_sections = _ksys_dlsym(libini, "ini_enum_sections");
		LIBINI_enum_keys = _ksys_dlsym(libini, "ini_enum_keys");
		LIBINI_get_str = _ksys_dlsym(libini, "ini_get_str");
		LIBINI_set_str = _ksys_dlsym(libini, "ini_set_str");
		LIBINI_set_color = _ksys_dlsym(libini, "ini_set_color");
		LIBINI_get_color = _ksys_dlsym(libini, "ini_get_color");
		LIBINI_set_int = _ksys_dlsym(libini, "ini_set_int");
		LIBINI_get_int = _ksys_dlsym(libini, "ini_get_int");
		LIBINI_get_shortcut = _ksys_dlsym(libini, "ini_get_shortcut");
		LIBINI_del_section = _ksys_dlsym(libini, "ini_del_section");

		if (LIBINI_enum_sections != NULL &&
			LIBINI_enum_keys != NULL &&
			LIBINI_get_str != NULL &&
			LIBINI_set_str != NULL &&
			LIBINI_get_color != NULL &&
			LIBINI_set_color != NULL &&
			LIBINI_set_int != NULL &&
			LIBINI_get_int != NULL &&
			LIBINI_get_shortcut != NULL &&
			LIBINI_del_section != NULL) // if all functions found
		{
#ifdef NDEBUG
			_ksys_debug_puts("successfully!\n");
#endif
			return 0; // OK
		}
	}

#ifdef NDEBUG
	_ksys_debug_puts("failed\n");
#endif
	return -1; // Error
}

int kolibri_libini_close()
{
	if (libini != NULL)
	{
		_ksys_free(libini);
		return 0;
	}
	else
	{
#ifdef NDEBUG
		_ksys_debug_puts("libini wasn't open yet!\n");
#endif
		return -1;
	}
}
