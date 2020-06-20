function(copy_to_target source destination)
	add_custom_command(TARGET ${source} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:${source}>
		$<TARGET_FILE_DIR:${destination}>/$<TARGET_FILE_NAME:${source}>)
endfunction()
