/* Copyright © 2005-2006  Roger Leigh <rleigh@debian.org>
 *
 * schroot is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * schroot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA  02111-1307  USA
 *
 *********************************************************************/

#include <config.h>

#include "sbuild-parse-value.h"

using namespace sbuild;

namespace
{

  typedef std::pair<parse_value_error_code,const char *> emap;

  /**
   * This is a list of the supported error codes.  It's used to
   * construct the real error codes map.
   */
  emap init_errors[] =
    {
      emap(BAD_VALUE, N_("Could not parse value '%1%'"))
    };

}

template<>
error<parse_value_error_code>::map_type
error<parse_value_error_code>::error_strings
(init_errors,
 init_errors + (sizeof(init_errors) / sizeof(init_errors[0])));

void
sbuild::parse_value (std::string const& value,
		     bool&              parsed_value)
{
  if (value == "true" || value == "yes" || value == "1")
    parsed_value = true;
  else if (value == "false" || value == "no" || value == "0")
    parsed_value = false;
  else
    {
      log_debug(DEBUG_NOTICE) << "parse error" << std::endl;
      throw parse_value_error(value, BAD_VALUE);
    }

  log_debug(DEBUG_NOTICE) << "value=" << parsed_value << std::endl;
}

void
sbuild::parse_value (std::string const& value,
		     std::string&       parsed_value)
{
  parsed_value = value;
  log_debug(DEBUG_NOTICE) << "value=" << parsed_value << std::endl;
}
