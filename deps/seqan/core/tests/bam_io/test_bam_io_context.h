// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2011, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Manuel Holtgrewe <manuel.holtgrewe@fu-berlin.de>
// ==========================================================================

#ifndef CORE_TESTS_BAM_IO_TEST_BAM_BAM_IO_CONTEXT_H_
#define CORE_TESTS_BAM_IO_TEST_BAM_BAM_IO_CONTEXT_H_

#include <seqan/basic.h>
#include <seqan/sequence.h>

#include <seqan/store.h>
#include <seqan/bam_io.h>

SEQAN_DEFINE_TEST(test_bam_io_bam_io_context_standalone)
{
    using namespace seqan;

    CharString ns;
    NameStoreCache<CharString> nsc(ns);
    BamIOContext<CharString> bamIOContext(ns, nsc);
    SEQAN_ASSERT_EQ(&ns, &nameStore(bamIOContext));
    SEQAN_ASSERT_EQ(&nsc, &nameStoreCache(bamIOContext));
}

SEQAN_DEFINE_TEST(test_bam_io_bam_io_context_fragment_store)
{
    using namespace seqan;

    typedef typename FragmentStore<>::TNameStore TNameStore;
    typedef NameStoreCache<TNameStore>           TNameStoreCache;

    FragmentStore<> store;
    BamIOContext<TNameStore, TNameStoreCache> bamIOContext(store.contigNameStore, store.contigNameStoreCache);
    SEQAN_ASSERT_EQ(&store.contigNameStore, &nameStore(bamIOContext));
    SEQAN_ASSERT_EQ(&store.contigNameStoreCache, &nameStoreCache(bamIOContext));
}

#endif  // CORE_TESTS_BAM_IO_TEST_BAM_BAM_IO_CONTEXT_H_
