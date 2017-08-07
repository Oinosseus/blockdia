#ifndef LIBBLOCKDIA_H
#define LIBBLOCKDIA_H

// this can be used as central include file users of the library

/**
 * @brief A library for managing block diagrams
 *
 * The data is stored in Block objects.
 * Blocks can be adjusted with Parameter objects.
 * There are different types of parameters available (int, string, enum).
 * Blocks can be connected together by their Input and Output objects.
 *
 * The library contains graphic views and edit widgets to show and edit blocks and block diagrams.
 *
 * The Block data hierarchy looks like this:
 * @image html BlockHierarchy.svg "Block data hierarchy" width=200px
 *
 */
namespace libblockdia {

}


// block data classes
#include <input.h>
#include <output.h>
#include <parameter.h>
#include <parameterint.h>
#include <block.h>

// block graphic classes
#include <viewblock.h>
#include <viewblockeditor.h>

#endif // LIBBLOCKDIA_H
