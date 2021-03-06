// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2012, Knut Reinert, FU Berlin
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
// Author: Andreas Gogol-Doering <andreas.doering@mdc-berlin.de>
// ==========================================================================
// The Align class provides tabular alignments.  It contains multiple
// Gap objects, one for each row of the alignment.
// ==========================================================================

#ifndef SEQAN_CORE_INCLUDE_SEQAN_ALIGN_ALIGN_BASE_H_
#define SEQAN_CORE_INCLUDE_SEQAN_ALIGN_ALIGN_BASE_H_

namespace seqan {

// ============================================================================
// Forwards
// ============================================================================

struct TagRaw_;
typedef Tag<TagRaw_> const Raw;

// ============================================================================
// Tags, Classes, Enums
// ============================================================================

// ----------------------------------------------------------------------------
// Class Align
// ----------------------------------------------------------------------------

/**
.Class.Align:
..cat:Alignments
..summary:An alignment of sequences.
..signature:Align<TSource, TSpec>
..param.TSource:Type of the ungapped sequences.
...metafunction:Metafunction.Source
..param.TSpec:The specializing type.
...metafunction:Metafunction.Spec
...default:@Spec.ArrayGaps@
..remarks:The default implementation of $Align$ stores the alignment in a set of @Class.Gaps|Gaps<TSource,TSpec>@ objects.
 Hence, the default implementation is row-based, so it will be faster to access the alignment row-wise than column-wise.
..include:seqan/align.h
*/

template <typename TSource, typename TSpec = ArrayGaps>
class Align
{
public:
    typedef Gaps<TSource, TSpec> TGaps;
    typedef String<TGaps> TRows;
    typedef typename Size<TRows>::Type TRowsSize;

    TRows data_rows;

    Align() {}

    template <typename TString, typename TStringsetSpec>
    Align(StringSet<TString, TStringsetSpec> & stringset)
    {
        setStrings(*this, stringset);
    }

    Align & operator=(Align const & other)
    {
        data_rows = other.data_rows;
        return *this;
    }
};

// ============================================================================
// Metafunctions
// ============================================================================

// ----------------------------------------------------------------------------
// Metafunction Cols
// ----------------------------------------------------------------------------

///.Metafunction.Cols.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct Cols<Align<TSource, TSpec> >
{
    typedef AlignCols<Align<TSource, TSpec> > Type;
};

template <typename TSource, typename TSpec>
struct Cols<Align<TSource, TSpec> const>
{
    typedef AlignCols<Align<TSource, TSpec> const> Type;
};

// ----------------------------------------------------------------------------
// Metafunction Value
// ----------------------------------------------------------------------------

///.Metafunction.Value.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct Value<Align<TSource, TSpec> >:
    Value<Gaps<TSource, TSpec> >
{};
template <typename TSource, typename TSpec>
struct Value<Align<TSource, TSpec> const>:
    Value<Gaps<TSource, TSpec> const>
{};

// ----------------------------------------------------------------------------
// Metafunction GetValue
// ----------------------------------------------------------------------------

///.Metafunction.GetValue.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct GetValue<Align<TSource, TSpec> >:
    GetValue<Gaps<TSource, TSpec> >
{};
template <typename TSource, typename TSpec>
struct GetValue<Align<TSource, TSpec> const>:
    GetValue<Gaps<TSource, TSpec> const>
{};

// ----------------------------------------------------------------------------
// Metafunction Reference
// ----------------------------------------------------------------------------

///.Metafunction.Reference.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct Reference<Align<TSource, TSpec> >:
    Reference<Gaps<TSource, TSpec> >
{};
template <typename TSource, typename TSpec>
struct Reference<Align<TSource, TSpec> const>:
    Reference<Gaps<TSource, TSpec> const>
{};

// ----------------------------------------------------------------------------
// Metafunction Rows
// ----------------------------------------------------------------------------

///.Metafunction.Rows.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct Rows<Align<TSource, TSpec> >
{
    typedef String<Gaps<TSource, TSpec> > Type;
};
template <typename TSource, typename TSpec>
struct Rows<Align<TSource, TSpec> const>
{
    typedef String<Gaps<TSource, TSpec> > const Type;
};

// ----------------------------------------------------------------------------
// Metafunction Source
// ----------------------------------------------------------------------------

///.Metafunction.Source.param.T.type:Class.Align

template <typename TSource, typename TSpec>
struct Source<Align<TSource, TSpec> >
{
    typedef TSource Type;
};
template <typename TSource, typename TSpec>
struct Source<Align<TSource, TSpec> const>
{
    typedef TSource Type;
};

// ----------------------------------------------------------------------------
// Metafunction StringSetType
// ----------------------------------------------------------------------------

template <typename TSource, typename TSpec>
struct StringSetType<Align<TSource, TSpec> >
{
    typedef StringSet<TSource, Dependent<> > Type;
};

template <typename TSource, typename TSpec>
struct StringSetType<Align<TSource, TSpec> const>
{
    typedef StringSet<TSource, Dependent<> > Type;
};

// ============================================================================
// Functions
// ============================================================================

// ----------------------------------------------------------------------------
// Function move()
// ----------------------------------------------------------------------------

template <typename TSource, typename TSpec>
inline
void move(Align<TSource, TSpec> & target, Align<TSource, TSpec> & source)
{
    move(target.data_rows, source.data_rows);
}

// ----------------------------------------------------------------------------
// Function rows()
// ----------------------------------------------------------------------------

/**
.Function.rows:
..cat:Alignments
..summary:The container of rows in an alignment.
..signature:Rows rows(align)
..param.align:An alignment.
...type:Class.Align
..returns:The container of rows in $align$.
...metafunction:Metafunction.Rows
..see:Function.cols
..see:Metafunction.Rows
..include:seqan/align.h
 */

template <typename TSource, typename TSpec>
inline typename Rows<Align<TSource, TSpec> >::Type &
rows(Align<TSource, TSpec> & me)
{
    return me.data_rows;
}

template <typename TSource, typename TSpec>
inline typename Rows<Align<TSource, TSpec> const>::Type &
rows(Align<TSource, TSpec> const & me)
{
    return me.data_rows;
}

// ----------------------------------------------------------------------------
// Function row()
// ----------------------------------------------------------------------------

/**
.Function.row:
..cat:Alignments
..summary:A row in an alignment.
..signature:Row & row(align, position)
..param.align:An alignment.
...type:Class.Align
..param.position:A position in the @Function.rows@ container of $align$.
..returns:The row in @Function.rows@ container of $align$ at the given $position$.
...metafunction:Metafunction.Row
..remarks:This function is equivalent to $value(rows(align), position)$.
..see:Function.rows
..see:Function.col
..see:Metafunction.Row
..include:seqan/align.h
 */

template <typename TSource, typename TSpec, typename TPosition>
inline typename Row<Align<TSource, TSpec> >::Type &
row(Align<TSource, TSpec> & me,
    TPosition _pos)
{
    return value(rows(me), _pos);
}

template <typename TSource, typename TSpec, typename TPosition>
inline typename Row<Align<TSource, TSpec> const>::Type &
row(Align<TSource, TSpec> const & me,
    TPosition _pos)
{
    return value(rows(me), _pos);
}

// ----------------------------------------------------------------------------
// Function cols()
// ----------------------------------------------------------------------------

/**
.Function.cols:
..cat:Alignments
..summary:The container of columns in an alignment.
..signature:Cols cols(align)
..param.align:An alignment.
...type:Class.Align
..returns:The container of columns in $align$.
...metafunction:Metafunction.Cols
..see:Metafunction.Cols
..include:seqan/align.h
*/

template <typename TSource, typename TSpec>
inline typename Cols<Align<TSource, TSpec> >::Type
cols(Align<TSource, TSpec> & me)
{
    return typename Cols<Align<TSource, TSpec> >::Type(me);
}

template <typename TSource, typename TSpec>
inline typename Cols<Align<TSource, TSpec> const>::Type
cols(Align<TSource, TSpec> const & me)
{
    return typename Cols<Align<TSource, TSpec> const>::Type(me);
}

// ----------------------------------------------------------------------------
// Function col()
// ----------------------------------------------------------------------------

/**
.Function.col:
..cat:Alignments
..summary:A column in an alignment.
..signature:Col & col(align, position)
..param.align:An alignment.
...type:Class.Align
..param.position:A position in the @Function.cols@ container of $align$.
..returns:The column in @Function.cols@ container of $align$ at the given $position$.
...metafunction:Metafunction.Col
..remarks:This function is equivalent to $value(cols(align), position)$.
..see:Function.cols
..see:Metafunction.Col
..include:seqan/align.h
*/

template <typename TSource, typename TSpec, typename TPosition>
inline typename Col<Align<TSource, TSpec> >::Type
col(Align<TSource, TSpec> & me,
    TPosition _pos)
{
    return value(cols(me), _pos);
}

template <typename TSource, typename TSpec, typename TPosition>
inline typename Col<Align<TSource, TSpec> const>::Type
col(Align<TSource, TSpec> const & me,
    TPosition _pos)
{
    return value(cols(me), _pos);
}

// ----------------------------------------------------------------------------
// Function detach()
// ----------------------------------------------------------------------------

///.Function.detach.param.object.type:Class.Align

template <typename TSource, typename TSpec>
inline void
detach(Align<TSource, TSpec> & me)
{
    typedef Align<TSource, TSpec> TAlign;
    typedef typename Rows<TAlign>::Type TRows;
    typedef typename Iterator<TRows, Standard>::Type TRowsIterator;

    TRowsIterator it = begin(rows(me));
    TRowsIterator it_end = end(rows(me));

    while (it != it_end)
    {
        detach(*it);
        ++it;
    }
}

// ----------------------------------------------------------------------------
// Function detach()
// ----------------------------------------------------------------------------

// TODO(holtgrew): Part of the old I/O system. Undocumented. Rename Raw() to HumanReadable() or OnScreen()?

template <typename TFile, typename TSource, typename TSpec, typename TIDString>
inline void
write(TFile & target,
      Align<TSource, TSpec> const & source,
      TIDString const &,
      Raw)
{
    typedef Align<TSource, TSpec> const TAlign;
    typedef typename Row<TAlign>::Type TRow;
    typedef typename Position<typename Rows<TAlign>::Type>::Type TRowsPosition;
    typedef typename Position<TAlign>::Type TPosition;

    TRowsPosition row_count = length(rows(source));
    TPosition begin_ = 0;
    TPosition end_ = std::min(length(row(source, 0)), length(row(source, 1)));

    unsigned int baseCount = 0;
    unsigned int leftSpace = 6;
    while (begin_ < end_)
    {
        unsigned int windowSize_ = 50;
        if ((begin_ + windowSize_) > end_)
            windowSize_ = end_ - begin_;

        // Print header line
        char buffer[100];
        sprintf(buffer, "%7u", (unsigned)baseCount);
        streamPut(target, buffer);
        baseCount += windowSize_;
        streamPut(target, ' ');
        for (TPosition i = 1; i <= windowSize_; ++i)
        {
            if ((i % 10) == 0)
                streamPut(target, ':');
            else if ((i % 5) == 0)
                streamPut(target, '.');
            else
                streamPut(target, ' ');
        }
        streamPut(target, ' ');
        streamPut(target, '\n');

        // Print sequences
        for (TRowsPosition i = 0; i < 2 * row_count - 1; ++i)
        {
            for (unsigned int j = 0; j < leftSpace + 2; ++j)
                streamPut(target, ' ');
            if ((i % 2) == 0)
            {
                TRow & row_ = row(source, i / 2);
                typedef typename Iterator<typename Row<TAlign>::Type const, Standard>::Type TIter;
                TIter begin1_ = iter(row_, begin_);
                TIter end1_ = iter(row_, begin_ + windowSize_);
                for (; begin1_ != end1_; ++begin1_)
                {
                    if (isGap(begin1_))
                        streamPut(target, gapValue<char>());
                    else
                        streamPut(target, *begin1_);
                }
            }
            else
            {
                for (unsigned int j = 0; j < windowSize_; ++j)
                {
                    if ((!isGap(row(source, (i - 1) / 2), begin_ + j)) &&
                        (!isGap(row(source, (i + 1) / 2), begin_ + j)) &&
                        (row(source, (i - 1) / 2)[begin_ + j] == row(source, (i + 1) / 2)[begin_ + j]))
                    {
                        streamPut(target, '|');
                    }
                    else
                    {
                        streamPut(target, ' ');
                    }
                }
            }
            streamPut(target, '\n');
        }
        streamPut(target, '\n');
        begin_ += 50;
    }
    streamPut(target, '\n');
}

// ----------------------------------------------------------------------------
// Function clearClipping()
// ----------------------------------------------------------------------------

// TODO(holtgrew): Undocumented.

template <typename TSource, typename TSpec>
inline void
clearClipping(Align<TSource, TSpec> & align_)
{
    typedef typename Rows<Align<TSource, TSpec> >::Type TRows;
    typedef typename Iterator<TRows>::Type TRowsIterator;

    for (TRowsIterator it = begin(rows(align_)); it != end(rows(align_)); goNext(it))
        clearClipping(*it);
}

// ----------------------------------------------------------------------------
// Function operator<<()
// ----------------------------------------------------------------------------

// stream operators

template <typename TStream, typename TSource, typename TSpec>
inline TStream &
operator<<(TStream & target,
           Align<TSource, TSpec> const & source)
{
    write(target, source);
    return target;
}

// ----------------------------------------------------------------------------
// Function setStrings()
// ----------------------------------------------------------------------------

/**
.Function.setStrings:
..cat:Alignments
..summary:Loads the sequences of a stringset into an alignment.
..signature:setStrings(align, stringset)
..param.align:An alignment.
...type:Class.Align
..param.stringset:A string set.
...type:Class.StringSet
..remarks:The function clears $align$ and creates an new global alignment between strings in $stringset$ that contains only trainling gaps.
The alignment will be dependent from the strings in the stringset; use @Function.detach@ to make $align$ the owner of its strings.
..include:seqan/align.h
 */

template <typename TSource, typename TSpec, typename TSpec2>
inline void
setStrings(Align<TSource, TSpec> & me,
           StringSet<TSource, TSpec2> & stringset)
{
    typedef Align<TSource, TSpec> TAlign;
    typedef StringSet<TSource, TSpec2> TStringset;

    typedef typename Rows<TAlign>::Type TRows;
    typedef typename Iterator<TRows>::Type TRowsIterator;
    typedef typename Size<TStringset>::Type TStringsetSize;

    clear(me.data_rows);
    resize(me.data_rows, length(stringset));
    TRowsIterator it = begin(rows(me));
    TStringsetSize stringset_length = length(stringset);
    for (TStringsetSize i = 0; i < stringset_length; ++i)
    {
        setSource(*it, value(stringset, i));
        ++it;
    }
}

// ----------------------------------------------------------------------------
// Function clearGaps()
// ----------------------------------------------------------------------------

template <typename TSource, typename TSpec>
inline void
clearGaps(Align<TSource, TSpec> & me)
{
    typedef Align<TSource, TSpec> TAlign;
    typedef typename Rows<TAlign>::Type TRows;
    typedef typename Iterator<TRows>::Type TRowsIterator;

    for (TRowsIterator it = begin(rows(me)); it != end(rows(me)); goNext(it))
        clearGaps(*it);
}

// ----------------------------------------------------------------------------
// Function stringSet()
// ----------------------------------------------------------------------------

/**
.Function.stringSet:
..param.g.type:Class.Align
..include:seqan/align.h
*/

template <typename TSource, typename TSpec>
inline typename StringSetType<Align<TSource, TSpec> >::Type
stringSet(Align<TSource, TSpec> & me)
{
    typedef Align<TSource, TSpec> TAlign;
    typedef typename StringSetType<TAlign>::Type TStringSet;

    typedef typename Rows<TAlign>::Type TRows;
    typedef typename Iterator<TRows>::Type TRowsIterator;

    TStringSet ss;

    for (TRowsIterator it = begin(rows(me)); it != end(rows(me)); goNext(it))
        appendValue(ss, source(*it));
    return ss;
}

// ----------------------------------------------------------------------------
// Function operator==()
// ----------------------------------------------------------------------------

template <typename TSource, typename TSpec>
inline bool operator==(Align<TSource, TSpec> const & lhs,
                       Align<TSource, TSpec> const & rhs)
{
    if (length(lhs.data_rows) != length(rhs.data_rows))
        return false;
    typedef typename Align<TSource, TSpec>::TGaps        TGaps;
    typedef typename Iterator<TGaps const, Rooted>::Type TIter;
    for (unsigned i = 0; i < length(rhs.data_rows); ++i)
        for (TIter itL = begin(lhs.data_rows[i], Rooted()), itR = begin(rhs.data_rows[i], Rooted()); !atEnd(itL); goNext(itL), goNext(itR))
            if (*itL != *itR)
                return false;
    return true;
}

// ----------------------------------------------------------------------------
// Function operator!=()
// ----------------------------------------------------------------------------

template <typename TSource, typename TSpec>
inline bool operator!=(Align<TSource, TSpec> const & lhs,
                       Align<TSource, TSpec> const & rhs)
{
    return !(lhs == rhs);
}

}  // namespace seqan

#endif  // #ifndef SEQAN_CORE_INCLUDE_SEQAN_ALIGN_ALIGN_BASE_H_
