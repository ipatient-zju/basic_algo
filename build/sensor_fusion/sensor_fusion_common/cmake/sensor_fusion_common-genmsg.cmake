# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "sensor_fusion_common: 3 messages, 0 services")

set(MSG_I_FLAGS "-Isensor_fusion_common:/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(sensor_fusion_common_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg" NAME_WE)
add_custom_target(_sensor_fusion_common_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sensor_fusion_common" "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg" NAME_WE)
add_custom_target(_sensor_fusion_common_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sensor_fusion_common" "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg" NAME_WE)
add_custom_target(_sensor_fusion_common_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sensor_fusion_common" "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg" "geometry_msgs/Point:geometry_msgs/Vector3:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_cpp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_cpp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common
)

### Generating Services

### Generating Module File
_generate_module_cpp(sensor_fusion_common
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(sensor_fusion_common_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(sensor_fusion_common_generate_messages sensor_fusion_common_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_cpp _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_cpp _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_cpp _sensor_fusion_common_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sensor_fusion_common_gencpp)
add_dependencies(sensor_fusion_common_gencpp sensor_fusion_common_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sensor_fusion_common_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_lisp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_lisp(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common
)

### Generating Services

### Generating Module File
_generate_module_lisp(sensor_fusion_common
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(sensor_fusion_common_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(sensor_fusion_common_generate_messages sensor_fusion_common_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_lisp _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_lisp _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_lisp _sensor_fusion_common_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sensor_fusion_common_genlisp)
add_dependencies(sensor_fusion_common_genlisp sensor_fusion_common_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sensor_fusion_common_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_py(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common
)
_generate_msg_py(sensor_fusion_common
  "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common
)

### Generating Services

### Generating Module File
_generate_module_py(sensor_fusion_common
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(sensor_fusion_common_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(sensor_fusion_common_generate_messages sensor_fusion_common_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/DoubleArrayStamped.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_py _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtEkf.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_py _sensor_fusion_common_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/aicrobo/basic_algo/src/sensor_fusion/sensor_fusion_common/msg/ExtState.msg" NAME_WE)
add_dependencies(sensor_fusion_common_generate_messages_py _sensor_fusion_common_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sensor_fusion_common_genpy)
add_dependencies(sensor_fusion_common_genpy sensor_fusion_common_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sensor_fusion_common_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sensor_fusion_common
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(sensor_fusion_common_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(sensor_fusion_common_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sensor_fusion_common
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(sensor_fusion_common_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(sensor_fusion_common_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sensor_fusion_common
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(sensor_fusion_common_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(sensor_fusion_common_generate_messages_py std_msgs_generate_messages_py)
