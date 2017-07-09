#ifndef LIBBLOCKDIA_H
#define LIBBLOCKDIA_H

#include <QtCore/qglobal.h>

#if defined(LIBBLOCKDIA_LIBRARY)
#  define LIBBLOCKDIASHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBBLOCKDIASHARED_EXPORT Q_DECL_IMPORT
#endif


namespace bd {

// forward declarations for contained classes
class Block;
class Parameter;
class Input;
class Output;

} // namespace bd


#endif // LIBBLOCKDIA_H
