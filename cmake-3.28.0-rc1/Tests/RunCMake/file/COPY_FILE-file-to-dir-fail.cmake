set(oldname "${CMAKE_CURRENT_BINARY_DIR}/input")
set(newname "${CMAKE_CURRENT_BINARY_DIR}/output")
file(WRITE "${oldname}" "")
file(MAKE_DIRECTORY "${newname}")
file(COPY_FILE "${oldname}" "${newname}")
