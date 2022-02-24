
set(EXO_SRC
        Isoparametrics.cpp
	Mesh.cpp
        PhysicalProperty.cpp
	PredictorCorrector.cpp
	ScalarMonotonic.cpp

   )

add_library(libexo STATIC ${EXO_SRC})
set_target_properties(libexo PROPERTIES OUTPUT_NAME exo)
target_include_directories(libexo PUBLIC ${PROJECT_SOURCE_DIR}/include)

