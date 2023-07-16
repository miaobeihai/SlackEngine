# Install script for directory: E:/ScrapEngine/external/reactphysics

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/REACTPHYSICS3D")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/ScrapEngine/external/reactphysics/lib/Debug/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/ScrapEngine/external/reactphysics/lib/Release/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/ScrapEngine/external/reactphysics/lib/MinSizeRel/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/ScrapEngine/external/reactphysics/lib/RelWithDebInfo/reactphysics3d.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/reactphysics3d" TYPE FILE FILES
    "E:/ScrapEngine/external/reactphysics/src/configuration.h"
    "E:/ScrapEngine/external/reactphysics/src/decimal.h"
    "E:/ScrapEngine/external/reactphysics/src/reactphysics3d.h"
    "E:/ScrapEngine/external/reactphysics/src/body/Body.h"
    "E:/ScrapEngine/external/reactphysics/src/body/CollisionBody.h"
    "E:/ScrapEngine/external/reactphysics/src/body/RigidBody.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/ContactPointInfo.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/ContactManifoldInfo.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/broadphase/BroadPhaseAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/broadphase/DynamicAABBTree.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/CollisionDispatch.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/DefaultCollisionDispatch.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/GJK/VoronoiSimplex.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/GJK/GJKAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/SAT/SATAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/NarrowPhaseAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/SphereVsSphereAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/SphereVsCapsuleAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/AABB.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/ConvexShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/ConvexPolyhedronShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/ConcaveShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/BoxShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/CapsuleShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/CollisionShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/ConvexMeshShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/SphereShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/TriangleShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/ConcaveMeshShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/shapes/HeightFieldShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/RaycastInfo.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/ProxyShape.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/TriangleVertexArray.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/PolygonVertexArray.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/TriangleMesh.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/PolyhedronMesh.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/HalfEdgeStructure.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/CollisionDetection.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/NarrowPhaseInfo.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/ContactManifold.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/ContactManifoldSet.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/MiddlePhaseTriangleCallback.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/BallAndSocketJoint.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/ContactPoint.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/FixedJoint.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/HingeJoint.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/Joint.h"
    "E:/ScrapEngine/external/reactphysics/src/constraint/SliderJoint.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/CollisionWorld.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/ConstraintSolver.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/ContactSolver.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/DynamicsWorld.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/EventListener.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/Island.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/Material.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/OverlappingPair.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/Timer.h"
    "E:/ScrapEngine/external/reactphysics/src/engine/Timer.cpp"
    "E:/ScrapEngine/external/reactphysics/src/collision/CollisionCallback.h"
    "E:/ScrapEngine/external/reactphysics/src/collision/OverlapCallback.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/mathematics.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/mathematics_functions.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Matrix2x2.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Matrix3x3.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Quaternion.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Transform.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Vector2.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Vector3.h"
    "E:/ScrapEngine/external/reactphysics/src/mathematics/Ray.h"
    "E:/ScrapEngine/external/reactphysics/src/memory/MemoryAllocator.h"
    "E:/ScrapEngine/external/reactphysics/src/memory/DefaultPoolAllocator.h"
    "E:/ScrapEngine/external/reactphysics/src/memory/DefaultSingleFrameAllocator.h"
    "E:/ScrapEngine/external/reactphysics/src/memory/DefaultAllocator.h"
    "E:/ScrapEngine/external/reactphysics/src/memory/MemoryManager.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/Stack.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/LinkedList.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/List.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/Map.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/Set.h"
    "E:/ScrapEngine/external/reactphysics/src/containers/Pair.h"
    "E:/ScrapEngine/external/reactphysics/src/utils/Profiler.h"
    "E:/ScrapEngine/external/reactphysics/src/utils/Logger.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/ScrapEngine/external/reactphysics/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
