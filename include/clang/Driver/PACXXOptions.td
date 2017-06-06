//===--- PACXXOptions.td - Options for clang-cl ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines the options for PACXX.
//
//===----------------------------------------------------------------------===//

def pacxx : Flag<["-"], "pacxx">, Flags<[CC1Option]>, HelpText<"Run clang in PACXX code gen mode">;