// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2010, Knut Reinert, FU Berlin
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
// Author: David Weese <david.weese@fu-berlin.de>
// ==========================================================================

#ifndef TESTS_INDEX_TEST_CROSS_COMPARE_H
#define TESTS_INDEX_TEST_CROSS_COMPARE_H

#include <typeinfo>

#include <seqan/index.h>

//////////////////////////////////////////////////////////////////////////////

namespace SEQAN_NAMESPACE_MAIN
{


template <typename TIter>
inline void _dumpState(TIter const it) 
{
	std::cout << typeid(it).name() << std::endl;
	std::cout << "  range:            " << value(it).range << std::endl;
	std::cout << "  countOccurrences: " << countOccurrences(it) << std::endl;
	std::cout << "  representative:   " << representative(it)   << std::endl;
	std::cout << "  parentEdgeLabel:  " << parentEdgeLabel(it)  << std::endl;
	std::cout << "  Occurrences:      ";
	for(unsigned i=0;i<countOccurrences(it);++i)
		std::cout << getOccurrences(it)[i] << " ";
	std::cout << std::endl;
}

template <typename TIterSpec, typename TIndex1, typename TIndex2>
void crossBottomUp(TIndex1 &index1, TIndex2 &index2)
{
	typename Iterator<TIndex1, TIterSpec>::Type iter1(index1);
	typename Iterator<TIndex2, TIterSpec>::Type iter2(index2);

	while (!atEnd(iter1) && !atEnd(iter2)) 
	{
		SEQAN_ASSERT_EQ(representative(iter1), representative(iter2));
		SEQAN_ASSERT_EQ(countOccurrences(iter1), countOccurrences(iter2));
		SEQAN_ASSERT_EQ(parentEdgeLength(iter1), parentEdgeLength(iter2));
		goNext(iter1);
		goNext(iter2);
	}
	SEQAN_ASSERT_EQ(atEnd(iter1), atEnd(iter2));
}

template <typename TIndexSpec1, typename TIndexSpec2, typename TText>
void crossIndex(TText &text)
{
	Index<TText, TIndexSpec1> index1(text);
	Index<TText, TIndexSpec2> index2(text);

/*	crossBottomUp< TopDown<ParentLinks<Preorder> > > (index1, index2);
	crossBottomUp< TopDown<ParentLinks<Postorder> > > (index1, index2);
*/	crossBottomUp< TopDown<ParentLinks<PreorderEmptyEdges> > > (index1, index2);
	crossBottomUp< TopDown<ParentLinks<PostorderEmptyEdges> > > (index1, index2);
}

template <typename TIndexSpec1, typename TIndexSpec2>
void crossIndicesChar()
{
/*	{
		CharString text("mississippi");
		crossIndex<TIndexSpec1,TIndexSpec2> (text);
	}
	{
		DnaString text("acaaacatat");
		crossIndex<TIndexSpec1,TIndexSpec2> (text);
	}
*/	{
		StringSet<CharString> t;
		resize(t, 6);
		t[0] = "caterpillar";
		t[1] = "catwoman";
		t[2] = "pillow";
		t[3] = "willow";
		t[4] = "ill";
		t[5] = "wow";
		crossIndex<TIndexSpec1,TIndexSpec2> (t);
  }
	/*{
		StringSet<DnaString> t;
		resize(t, 6);
		t[0] = "caggctcgcgt";
		t[1] = "caggaacg";
		t[2] = "tcgttg";
		t[3] = "tggtcg";
		t[4] = "agg";
		t[5] = "ctg";
		crossIndex<TIndexSpec1,TIndexSpec2> (t);
	}*/
}

template <typename TIndexSpec1, typename TIndexSpec2>
void crossIndicesDna()
{
/*	{
		CharString text("mississippi");
		crossIndex<TIndexSpec1,TIndexSpec2> (text);
	}
	{
		DnaString text("acaaacatat");
		crossIndex<TIndexSpec1,TIndexSpec2> (text);
	}
*//*	{
		StringSet<CharString> t;
		resize(t, 6);
		t[0] = "caterpillar";
		t[1] = "catwoman";
		t[2] = "pillow";
		t[3] = "willow";
		t[4] = "ill";
		t[5] = "wow";
		crossIndex<TIndexSpec1,TIndexSpec2> (t);
	}*/
	{
		StringSet<DnaString> t;
		resize(t, 6);
		t[0] = "caggctcgcgt";
		t[1] = "caggaacg";
		t[2] = "tcgttg";
		t[3] = "tggtcg";
		t[4] = "agg";
		t[5] = "ctg";
		crossIndex<TIndexSpec1,TIndexSpec2> (t);
	}
}

SEQAN_DEFINE_TEST(testIndexCrossCompareChar)
{
	crossIndicesChar<IndexEsa<>, IndexWotd<> >();
	crossIndicesChar<IndexWotd<>, IndexWotd<Dfi<> > >();
}

SEQAN_DEFINE_TEST(testIndexCrossCompareDna)
{
	crossIndicesDna<IndexEsa<>, IndexWotd<> >();
	crossIndicesDna<IndexWotd<>, IndexWotd<Dfi<> > >();
}

//////////////////////////////////////////////////////////////////////////////


} //namespace SEQAN_NAMESPACE_MAIN

#endif //#ifndef SEQAN_HEADER_...
