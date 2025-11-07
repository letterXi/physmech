add_executable(cheharda 
		Cheharda.cpp
)

add_executable(kranknick
		KrankNick.cpp
)

add_executable(lakswendorff
		LaksWendorff.cpp
)

target_link_libraries(kranknick amgsollib)
