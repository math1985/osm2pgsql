#ifndef OSMIUM_OSM_OBJECT_COMPARISONS_HPP
#define OSMIUM_OSM_OBJECT_COMPARISONS_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013-2015 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <osmium/osm/object.hpp>

namespace osmium {

    /**
     * Function object class for comparing OSM objects for equality by type, id, and version.
     */
    struct object_equal_type_id_version {

        bool operator()(const osmium::OSMObject& lhs, const osmium::OSMObject& rhs) const noexcept {
            return lhs == rhs;
        }

        bool operator()(const osmium::OSMObject* lhs, const osmium::OSMObject* rhs) const noexcept {
            return *lhs == *rhs;
        }

    }; // struct object_equal_type_id_version

    /**
     * Function object class for comparing OSM objects for equality by type and id,
     * ignoring the version.
     */
    struct object_equal_type_id {

        bool operator()(const osmium::OSMObject& lhs, const osmium::OSMObject& rhs) const noexcept {
            return lhs.type() == rhs.type() &&
                   lhs.id() == rhs.id();
        }

        bool operator()(const osmium::OSMObject* lhs, const osmium::OSMObject* rhs) const noexcept {
            return operator()(*lhs, *rhs);
        }

    }; // struct object_equal_type_id

    /**
     * Function object class for ordering OSM objects by type, id, and version.
     */
    struct object_order_type_id_version {

        bool operator()(const osmium::OSMObject& lhs, const osmium::OSMObject& rhs) const noexcept {
            return lhs < rhs;
        }

        bool operator()(const osmium::OSMObject* lhs, const osmium::OSMObject* rhs) const noexcept {
            return *lhs < *rhs;
        }

    }; // struct object_order_type_id_version

    /**
     * Function object class for ordering OSM objects by type, id, and reverse version,
     * ie objects are ordered by type and id, but later versions of an object are
     * ordered before earlier versions of the same object.
     */
    struct object_order_type_id_reverse_version {

        bool operator()(const osmium::OSMObject& lhs, const osmium::OSMObject& rhs) const noexcept {
            if (lhs.type() != rhs.type()) {
                return lhs.type() < rhs.type();
            }
            return (lhs.id() == rhs.id() && lhs.version() > rhs.version()) ||
                   lhs.positive_id() < rhs.positive_id();
        }

        bool operator()(const osmium::OSMObject* lhs, const osmium::OSMObject* rhs) const noexcept {
            return operator()(*lhs, *rhs);
        }

    }; // struct object_order_type_id_reverse_version

} // namespace osmium

#endif // OSMIUM_OSM_OBJECT_COMPARISONS_HPP
