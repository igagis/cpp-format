include prorab.mk
include prorab-test.mk

$(eval $(call prorab-config, config))

this_name := cpp-format

this_srcs := $(call prorab-src-dir, src)

this_ldlibs += -lutki

$(eval $(prorab-build-app))

this_run_name := $(this_name)
this_test_cmd := $(prorab_this_name)
this_test_deps := $(prorab_this_name)
this_test_ld_path := $(prorab_space)
$(eval $(prorab-run))


$(eval $(prorab-include-subdirs))
