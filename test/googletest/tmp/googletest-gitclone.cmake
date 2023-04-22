if("master" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitinfo.txt" IS_NEWER_THAN "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest'")
endif()

set(git_options)

# disable cert checking if explicitly told not to do it
set(tls_verify "")
if(NOT "x" STREQUAL "x" AND NOT tls_verify)
  list(APPEND git_options
    -c http.sslVerify=false)
endif()

set(git_clone_options)

set(git_shallow "")
if(git_shallow)
  list(APPEND git_clone_options --depth 1 --no-single-branch)
endif()

set(git_progress "")
if(git_progress)
  list(APPEND git_clone_options --progress)
endif()

set(git_config "")
foreach(config IN LISTS git_config)
  list(APPEND git_clone_options --config ${config})
endforeach()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "D:/DevelopmentEnvironment/Softwares/Git/cmd/git.exe" ${git_options} clone ${git_clone_options} --origin "origin" "https://github.com/google/googletest" "googletest"
    WORKING_DIRECTORY "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/google/googletest'")
endif()

execute_process(
  COMMAND "D:/DevelopmentEnvironment/Softwares/Git/cmd/git.exe" ${git_options} checkout master --
  WORKING_DIRECTORY "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

execute_process(
  COMMAND "D:/DevelopmentEnvironment/Softwares/Git/cmd/git.exe" ${git_options} submodule init 
  WORKING_DIRECTORY "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: 'D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest'")
endif()

execute_process(
  COMMAND "D:/DevelopmentEnvironment/Softwares/Git/cmd/git.exe" ${git_options} submodule update --recursive --init 
  WORKING_DIRECTORY "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitinfo.txt"
    "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitclone-lastrun.txt"
  WORKING_DIRECTORY "D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/DevelopmentEnvironment/Workspaces/VisualStudio2015Projects/Cpp/webdriverxx/vcprojects/test/googletest/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
endif()

