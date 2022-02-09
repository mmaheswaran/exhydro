
set(EXO_SRC
	Mesh.cpp
	PredictorCorrector.cpp
	#ScalarMonotonic.cpp
        Isoparametrics.cpp
   )

add_library(libexo STATIC ${EXO_SRC})
set_target_properties(libexo PROPERTIES OUTPUT_NAME exo)
target_include_directories(libexo PUBLIC ${PROJECT_SOURCE_DIR}/include)

