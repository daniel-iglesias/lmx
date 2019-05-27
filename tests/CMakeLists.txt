IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(BOOST_ROOT "C:/Users/Daniel/Libraries/boost_1_66_0") # either set it here or from the command line 
find_package(Boost)

include_directories (
  ${LMX_SOURCE_DIR}/src/
  ${Boost_INCLUDE_DIRS}
)
SET(My_Headers
	${LMX_SOURCE_DIR}/src/LMX/lmx_diff_problem_double.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_diff_problem_first.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_diff_problem_first_second.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_diff_problem_second.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_except.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers_cg.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers_lapack.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers_lu.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers_superlu_interface.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_linsolvers_system.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_data.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_data_blas.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_data_mat.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_data_vec.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_dense_matrix.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_elem_ref.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_matrix.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_csc.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_gmm.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_gmmvector_sparse1.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_gmm_sparse1.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_stdmatrix.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_type_stdvector.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_mat_vector.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_nlsolvers.h
	${LMX_SOURCE_DIR}/src/LMX/lmx_nlsolvers_double.h
)

source_group("My Headers" FILES ${My_Headers})



set(Inputs 001 002 003 004 005 006 007 008 009 010 011 012 013 014)
foreach(Input ${Inputs})
  add_executable (test${Input} test${Input}.cpp ${My_Headers})
  add_test(NAME Test${Input} COMMAND test${Input})
endforeach()

