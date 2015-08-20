#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnnamedSoftware
TEMPLATE = app

SOURCES += gui/main.cpp\
    gui/mainwindow.cpp \
    gui/mygraphicsview.cpp \
    gui/myitemmodel.cpp \
    gui/blockgraphicsitem.cpp \
    flowchart/block.cpp \
    flowchart/blocktype.cpp \
    flowchart/flowchart.cpp \
    jsoncpp.cpp \
    usb/deviceconnection.cpp \
    compiler/compiler.cpp

HEADERS  += gui/mainwindow.h \
    gui/mygraphicsview.h \
    gui/myitemmodel.h \
    gui/blockgraphicsitem.h \
    flowchart/block.h \
    flowchart/blocktype.h \
    flowchart/flowchart.h \
    json/json.h \
    json/json-forwards.h \
    usb/deviceconnection.h \
    blocks/addition.h \
    blocks/input.h \
    blocks/output.h \
    boost/config/abi/borland_prefix.hpp \
    boost/config/abi/borland_suffix.hpp \
    boost/config/abi/msvc_prefix.hpp \
    boost/config/abi/msvc_suffix.hpp \
    boost/config/compiler/borland.hpp \
    boost/config/compiler/clang.hpp \
    boost/config/compiler/codegear.hpp \
    boost/config/compiler/comeau.hpp \
    boost/config/compiler/common_edg.hpp \
    boost/config/compiler/compaq_cxx.hpp \
    boost/config/compiler/cray.hpp \
    boost/config/compiler/digitalmars.hpp \
    boost/config/compiler/gcc.hpp \
    boost/config/compiler/gcc_xml.hpp \
    boost/config/compiler/greenhills.hpp \
    boost/config/compiler/hp_acc.hpp \
    boost/config/compiler/intel.hpp \
    boost/config/compiler/kai.hpp \
    boost/config/compiler/metrowerks.hpp \
    boost/config/compiler/nvcc.hpp \
    boost/config/compiler/pathscale.hpp \
    boost/config/compiler/pgi.hpp \
    boost/config/compiler/sgi_mipspro.hpp \
    boost/config/compiler/sunpro_cc.hpp \
    boost/config/compiler/vacpp.hpp \
    boost/config/compiler/visualc.hpp \
    boost/config/no_tr1/cmath.hpp \
    boost/config/no_tr1/complex.hpp \
    boost/config/no_tr1/functional.hpp \
    boost/config/no_tr1/memory.hpp \
    boost/config/no_tr1/utility.hpp \
    boost/config/platform/aix.hpp \
    boost/config/platform/amigaos.hpp \
    boost/config/platform/beos.hpp \
    boost/config/platform/bsd.hpp \
    boost/config/platform/cray.hpp \
    boost/config/platform/cygwin.hpp \
    boost/config/platform/hpux.hpp \
    boost/config/platform/irix.hpp \
    boost/config/platform/linux.hpp \
    boost/config/platform/macos.hpp \
    boost/config/platform/qnxnto.hpp \
    boost/config/platform/solaris.hpp \
    boost/config/platform/symbian.hpp \
    boost/config/platform/vms.hpp \
    boost/config/platform/vxworks.hpp \
    boost/config/platform/win32.hpp \
    boost/config/stdlib/dinkumware.hpp \
    boost/config/stdlib/libcomo.hpp \
    boost/config/stdlib/libcpp.hpp \
    boost/config/stdlib/libstdcpp3.hpp \
    boost/config/stdlib/modena.hpp \
    boost/config/stdlib/msl.hpp \
    boost/config/stdlib/roguewave.hpp \
    boost/config/stdlib/sgi.hpp \
    boost/config/stdlib/stlport.hpp \
    boost/config/stdlib/vacpp.hpp \
    boost/config/abi_prefix.hpp \
    boost/config/abi_suffix.hpp \
    boost/config/auto_link.hpp \
    boost/config/posix_features.hpp \
    boost/config/requires_threads.hpp \
    boost/config/select_compiler_config.hpp \
    boost/config/select_platform_config.hpp \
    boost/config/select_stdlib_config.hpp \
    boost/config/suffix.hpp \
    boost/config/user.hpp \
    boost/config/warning_disable.hpp \
    boost/detail/container_fwd.hpp \
    boost/detail/workaround.hpp \
    boost/functional/hash/detail/float_functions.hpp \
    boost/functional/hash/detail/hash_float.hpp \
    boost/functional/hash/detail/limits.hpp \
    boost/functional/hash/extensions.hpp \
    boost/functional/hash/hash.hpp \
    boost/functional/hash/hash_fwd.hpp \
    boost/integer/static_log2.hpp \
    boost/mpl/aux_/config/adl.hpp \
    boost/mpl/aux_/config/arrays.hpp \
    boost/mpl/aux_/config/ctps.hpp \
    boost/mpl/aux_/config/gcc.hpp \
    boost/mpl/aux_/config/intel.hpp \
    boost/mpl/aux_/config/lambda.hpp \
    boost/mpl/aux_/config/msvc.hpp \
    boost/mpl/aux_/config/overload_resolution.hpp \
    boost/mpl/aux_/config/preprocessor.hpp \
    boost/mpl/aux_/config/static_constant.hpp \
    boost/mpl/aux_/config/ttp.hpp \
    boost/mpl/aux_/config/workaround.hpp \
    boost/mpl/aux_/preprocessor/enum.hpp \
    boost/mpl/aux_/preprocessor/params.hpp \
    boost/mpl/aux_/adl_barrier.hpp \
    boost/mpl/aux_/integral_wrapper.hpp \
    boost/mpl/aux_/lambda_support.hpp \
    boost/mpl/aux_/na_fwd.hpp \
    boost/mpl/aux_/static_cast.hpp \
    boost/mpl/aux_/template_arity_fwd.hpp \
    boost/mpl/aux_/yes_no.hpp \
    boost/mpl/bool.hpp \
    boost/mpl/bool_fwd.hpp \
    boost/mpl/int.hpp \
    boost/mpl/int_fwd.hpp \
    boost/mpl/integral_c.hpp \
    boost/mpl/integral_c_fwd.hpp \
    boost/mpl/integral_c_tag.hpp \
    boost/preprocessor/arithmetic/add.hpp \
    boost/preprocessor/arithmetic/dec.hpp \
    boost/preprocessor/arithmetic/inc.hpp \
    boost/preprocessor/arithmetic/sub.hpp \
    boost/preprocessor/array/data.hpp \
    boost/preprocessor/array/elem.hpp \
    boost/preprocessor/array/size.hpp \
    boost/preprocessor/config/config.hpp \
    boost/preprocessor/control/detail/dmc/while.hpp \
    boost/preprocessor/control/detail/edg/while.hpp \
    boost/preprocessor/control/detail/msvc/while.hpp \
    boost/preprocessor/control/detail/while.hpp \
    boost/preprocessor/control/expr_iif.hpp \
    boost/preprocessor/control/if.hpp \
    boost/preprocessor/control/iif.hpp \
    boost/preprocessor/control/while.hpp \
    boost/preprocessor/debug/error.hpp \
    boost/preprocessor/detail/dmc/auto_rec.hpp \
    boost/preprocessor/detail/auto_rec.hpp \
    boost/preprocessor/detail/check.hpp \
    boost/preprocessor/detail/is_binary.hpp \
    boost/preprocessor/facilities/empty.hpp \
    boost/preprocessor/facilities/overload.hpp \
    boost/preprocessor/iteration/detail/bounds/lower1.hpp \
    boost/preprocessor/iteration/detail/bounds/lower2.hpp \
    boost/preprocessor/iteration/detail/bounds/lower3.hpp \
    boost/preprocessor/iteration/detail/bounds/lower4.hpp \
    boost/preprocessor/iteration/detail/bounds/lower5.hpp \
    boost/preprocessor/iteration/detail/bounds/upper1.hpp \
    boost/preprocessor/iteration/detail/bounds/upper2.hpp \
    boost/preprocessor/iteration/detail/bounds/upper3.hpp \
    boost/preprocessor/iteration/detail/bounds/upper4.hpp \
    boost/preprocessor/iteration/detail/bounds/upper5.hpp \
    boost/preprocessor/iteration/detail/iter/forward1.hpp \
    boost/preprocessor/iteration/detail/iter/forward2.hpp \
    boost/preprocessor/iteration/detail/iter/forward3.hpp \
    boost/preprocessor/iteration/detail/iter/forward4.hpp \
    boost/preprocessor/iteration/detail/iter/forward5.hpp \
    boost/preprocessor/iteration/detail/iter/reverse1.hpp \
    boost/preprocessor/iteration/detail/iter/reverse2.hpp \
    boost/preprocessor/iteration/detail/iter/reverse3.hpp \
    boost/preprocessor/iteration/detail/iter/reverse4.hpp \
    boost/preprocessor/iteration/detail/iter/reverse5.hpp \
    boost/preprocessor/iteration/detail/finish.hpp \
    boost/preprocessor/iteration/detail/local.hpp \
    boost/preprocessor/iteration/detail/rlocal.hpp \
    boost/preprocessor/iteration/detail/self.hpp \
    boost/preprocessor/iteration/detail/start.hpp \
    boost/preprocessor/iteration/iterate.hpp \
    boost/preprocessor/iteration/local.hpp \
    boost/preprocessor/iteration/self.hpp \
    boost/preprocessor/list/detail/dmc/fold_left.hpp \
    boost/preprocessor/list/detail/edg/fold_left.hpp \
    boost/preprocessor/list/detail/edg/fold_right.hpp \
    boost/preprocessor/list/detail/fold_left.hpp \
    boost/preprocessor/list/detail/fold_right.hpp \
    boost/preprocessor/list/adt.hpp \
    boost/preprocessor/list/fold_left.hpp \
    boost/preprocessor/list/fold_right.hpp \
    boost/preprocessor/list/for_each_i.hpp \
    boost/preprocessor/list/reverse.hpp \
    boost/preprocessor/logical/bitand.hpp \
    boost/preprocessor/logical/bool.hpp \
    boost/preprocessor/logical/compl.hpp \
    boost/preprocessor/punctuation/comma.hpp \
    boost/preprocessor/punctuation/comma_if.hpp \
    boost/preprocessor/repetition/detail/dmc/for.hpp \
    boost/preprocessor/repetition/detail/edg/for.hpp \
    boost/preprocessor/repetition/detail/msvc/for.hpp \
    boost/preprocessor/repetition/detail/for.hpp \
    boost/preprocessor/repetition/enum_params.hpp \
    boost/preprocessor/repetition/for.hpp \
    boost/preprocessor/repetition/repeat.hpp \
    boost/preprocessor/repetition/repeat_from_to.hpp \
    boost/preprocessor/slot/detail/counter.hpp \
    boost/preprocessor/slot/detail/def.hpp \
    boost/preprocessor/slot/detail/shared.hpp \
    boost/preprocessor/slot/detail/slot1.hpp \
    boost/preprocessor/slot/detail/slot2.hpp \
    boost/preprocessor/slot/detail/slot3.hpp \
    boost/preprocessor/slot/detail/slot4.hpp \
    boost/preprocessor/slot/detail/slot5.hpp \
    boost/preprocessor/slot/slot.hpp \
    boost/preprocessor/tuple/eat.hpp \
    boost/preprocessor/tuple/elem.hpp \
    boost/preprocessor/tuple/rem.hpp \
    boost/preprocessor/tuple/size.hpp \
    boost/preprocessor/tuple/to_list.hpp \
    boost/preprocessor/variadic/elem.hpp \
    boost/preprocessor/variadic/size.hpp \
    boost/preprocessor/cat.hpp \
    boost/preprocessor/comma_if.hpp \
    boost/preprocessor/enum_params.hpp \
    boost/preprocessor/inc.hpp \
    boost/preprocessor/iterate.hpp \
    boost/preprocessor/repeat.hpp \
    boost/type_traits/detail/bool_trait_def.hpp \
    boost/type_traits/detail/bool_trait_undef.hpp \
    boost/type_traits/detail/cv_traits_impl.hpp \
    boost/type_traits/detail/false_result.hpp \
    boost/type_traits/detail/ice_and.hpp \
    boost/type_traits/detail/ice_eq.hpp \
    boost/type_traits/detail/ice_not.hpp \
    boost/type_traits/detail/ice_or.hpp \
    boost/type_traits/detail/is_function_ptr_helper.hpp \
    boost/type_traits/detail/is_function_ptr_tester.hpp \
    boost/type_traits/detail/is_mem_fun_pointer_impl.hpp \
    boost/type_traits/detail/is_mem_fun_pointer_tester.hpp \
    boost/type_traits/detail/template_arity_spec.hpp \
    boost/type_traits/detail/type_trait_def.hpp \
    boost/type_traits/detail/type_trait_undef.hpp \
    boost/type_traits/detail/yes_no_type.hpp \
    boost/type_traits/add_lvalue_reference.hpp \
    boost/type_traits/add_reference.hpp \
    boost/type_traits/add_rvalue_reference.hpp \
    boost/type_traits/config.hpp \
    boost/type_traits/ice.hpp \
    boost/type_traits/integral_constant.hpp \
    boost/type_traits/intrinsics.hpp \
    boost/type_traits/is_abstract.hpp \
    boost/type_traits/is_arithmetic.hpp \
    boost/type_traits/is_array.hpp \
    boost/type_traits/is_class.hpp \
    boost/type_traits/is_convertible.hpp \
    boost/type_traits/is_enum.hpp \
    boost/type_traits/is_float.hpp \
    boost/type_traits/is_function.hpp \
    boost/type_traits/is_integral.hpp \
    boost/type_traits/is_lvalue_reference.hpp \
    boost/type_traits/is_member_function_pointer.hpp \
    boost/type_traits/is_member_pointer.hpp \
    boost/type_traits/is_pointer.hpp \
    boost/type_traits/is_polymorphic.hpp \
    boost/type_traits/is_reference.hpp \
    boost/type_traits/is_rvalue_reference.hpp \
    boost/type_traits/is_same.hpp \
    boost/type_traits/is_scalar.hpp \
    boost/type_traits/is_union.hpp \
    boost/type_traits/is_void.hpp \
    boost/type_traits/is_volatile.hpp \
    boost/type_traits/remove_bounds.hpp \
    boost/type_traits/remove_cv.hpp \
    boost/type_traits/remove_reference.hpp \
    boost/utility/enable_if.hpp \
    boost/assert.hpp \
    boost/config.hpp \
    boost/cstdint.hpp \
    boost/current_function.hpp \
    boost/integer_fwd.hpp \
    boost/limits.hpp \
    boost/static_assert.hpp \
    boost/version.hpp \
    compiler/compiler.h

FORMS    += gui/mainwindow.ui

RESOURCES += \
    gui/resources.qrc

win32 {
    INCLUDEPATH += $$(LIBUSBDIR)/libusb/
    !contains(QMAKE_TARGET.arch, x86_64) {
        #Win32
        LIBS += -L$$(LIBUSBDIR)/Win32/Release/lib/
    } else {
        #Win64
        LIBS += -L$$(LIBUSBDIR)/x64/Release/lib/
    }
    LIBS += -llibusb-1.0
}
linux-g++ {
    INCLUDEPATH += /usr/include/libusb-1.0/
    LIBS += -L/usr/lib/
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += -lusb-1.0
}


