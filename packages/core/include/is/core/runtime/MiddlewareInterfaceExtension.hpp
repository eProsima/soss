/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 * Copyright (C) 2020 - present Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _IS_CORE_RUNTIME_MIDDLEWAREINTERFACEEXTENSION_HPP_
#define _IS_CORE_RUNTIME_MIDDLEWAREINTERFACEEXTENSION_HPP_

#include <yaml-cpp/yaml.h>

#include <is/core/export.hpp>
#include <is/utils/Log.hpp>

#include <memory>

namespace eprosima {
namespace is {
namespace core {

/**
 * @class MiddlewareInterfaceExtension
 *        Abbreviated as "Mix", allows to generate *mix* files which contain the
 *        required dynamic libraries for a certain Integration Service instance
 *        to be loaded.
 *
 *        Also, when talking about a specific SystemHandle, *mix* files are used
 *        to list the necessary dynamic libraries, containing information about
 *        conversion from the specific middleware data type definition (such as ROS 2 *msg*)
 *        to <a href="https://github.com/eProsima/xtypes">xtypes</a>, and viceversa.
 *
 *        Libraries within the *mix* file are listed using the following structure:
 *        - For Linux systems: `"dl" : "../../<relative_path_to_dl>"`
 *        - On Windows platforms: `"dll" : "../../<relative/path_to_dll>"`
 *
 *        This extensions are automatically generated by *is_mix_generator*
 *        CMake function and they contain information about specific types,
 *        such as their conversion methods to/from `xtypes`.
 */
class IS_CORE_API MiddlewareInterfaceExtension
{
public:

    /**
     * @brief Constructor.
     *
     * @param[in] mix_content Movable reference representing the content of the *mix* file.
     *
     * @param[in] absolute_file_directory_path Absolute path where the *mix* file is stored.
     *            This path will be later on used as a starting point to navigate to the
     *            relative paths defined by the *mix* file, so that dynamic libraries can
     *            be loaded.
     */
    MiddlewareInterfaceExtension(
            YAML::Node&& mix_content,
            const std::string& absolute_file_directory_path);

    /**
     * @brief MiddlewareInterfaceExtension shall not be copy constructible.
     */
    MiddlewareInterfaceExtension(
            const MiddlewareInterfaceExtension& other) = delete;

    /**
     * @brief Move constructor.
     *
     * @param[in] other Movable reference to another MiddlewareInterfaceExtension instance.
     */
    MiddlewareInterfaceExtension(
            MiddlewareInterfaceExtension&& other);

    /**
     * @brief Destructor.
     */
    ~MiddlewareInterfaceExtension();

    /**
     * @brief Create a MiddlewareInterfaceExtension representation from a *mix* file path.
     *
     * @param[in] filename Path to the *mix* file.
     *
     * @returns A properly initialized MiddlewareInterfaceExtension object.
     */
    static MiddlewareInterfaceExtension from_file(
            const std::string& filename);

    /**
     * @brief Create a MiddlewareInterfaceExtension representation from a text YAML
     *        representation and an absolute file directory path.
     *
     * @param[in] mix_text Content of the *mix* file, in text format.
     *
     * @param[in] absolute_file_directory_path Path from where to start looking for
     *            dynamic libraries defined in the *mix* content.
     *
     * @returns A properly initialized MiddlewareInterfaceExtension object.
     */
    static MiddlewareInterfaceExtension from_string(
            const std::string& mix_text,
            const std::string& absolute_file_directory_path);

    /**
     * @brief Create a MiddlewareInterfaceExtension representation from a YAML node
     *        representation and an absolute file directory path.
     *
     * @param[in] node Content of the *mix* file, in YAML format.
     *
     * @param[in] absolute_file_directory_path Path from where to start looking for
     *            dynamic libraries defined in the *mix* content.
     *
     * @returns A properly initialized MiddlewareInterfaceExtension object.
     */
    static MiddlewareInterfaceExtension from_node(
            YAML::Node&& node,
            const std::string& absolute_file_directory_path);

    /**
     * @brief Performs the load operation of the defined dynamic libraries in the
     *        *mix* file.
     *
     * @returns `true` if the dynamic libraries were loaded successfully, or
     *          `false` otherwise.
     */
    bool load();

private:

    /**
     * @class Implementation
     *        Defines the actual implementation of the MiddlewareInterfaceExtension class.
     *
     *        Allows to use the *pimpl* procedure to separate the implementation
     *        from the interface of MiddlewareInterfaceExtension.
     *
     *        Methods named equal to some MiddlewareInterfaceExtension method will not be
     *        documented again. Usually, the interface class will call to
     *        `_pimpl->method()`, but the functionality and parameters
     *        are exactly the same.
     */
    class Implementation;

    /**
     * Class members.
     */

    std::unique_ptr<Implementation> _pimpl;
};

using Mix = MiddlewareInterfaceExtension;

} //  namespace core
} //  namespace is
} //  namespace eprosima

#endif //  _IS_CORE_RUNTIME_MIDDLEWAREINTERFACEEXTENSION_HPP_
