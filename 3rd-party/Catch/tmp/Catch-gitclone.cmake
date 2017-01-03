if("v1.5.9" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitinfo.txt" IS_NEWER_THAN "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" clone --origin "origin" "https://github.com/philsquared/Catch.git" "Catch"
    WORKING_DIRECTORY "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/philsquared/Catch.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" checkout v1.5.9
  WORKING_DIRECTORY "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v1.5.9'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" submodule init 
  WORKING_DIRECTORY "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: 'D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" submodule update --recursive 
  WORKING_DIRECTORY "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitinfo.txt"
    "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitclone-lastrun.txt"
  WORKING_DIRECTORY "D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/School/CWU/CS 481/Lots-of-Lines/3rd-party/Catch/src/Catch-stamp/Catch-gitclone-lastrun.txt'")
endif()

