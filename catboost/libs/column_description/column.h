#pragma once

#include <library/cpp/binsaver/bin_saver.h>

#include <util/ysaveload.h>
#include <util/generic/string.h>

enum class EColumn {
    Num,
    Categ,
    HashedCateg,
    Label,
    Auxiliary,
    Baseline,
    Weight,
    SampleId,
    GroupId,
    GroupWeight,
    SubgroupId,
    Timestamp,
    Sparse,
    Prediction,
    Text,
    NumVector
};

inline bool IsFactorColumn(EColumn column) {
    switch (column) {
        case EColumn::Num:
        case EColumn::Categ:
        case EColumn::HashedCateg:
        case EColumn::Sparse:
        case EColumn::Text:
        case EColumn::NumVector:
            return true;
        default:
            return false;
    }
}

inline bool CanBeOutputByColumnType(EColumn column) {
    return column == EColumn::Label ||
           column == EColumn::Baseline ||
           column == EColumn::Weight ||
           column == EColumn::SampleId ||
           column == EColumn::GroupId ||
           column == EColumn::GroupWeight ||
           column == EColumn::SubgroupId ||
           column == EColumn::Timestamp ||
           column == EColumn::Prediction;
}

TStringBuf ToCanonicalColumnName(TStringBuf columnName);

void ParseOutputColumnByIndex(const TString& outputColumn, ui32* columnNumber, TString* name);

struct TColumn {
    EColumn Type;
    TString Id;

public:
    bool operator==(const TColumn& rhs) const {
        return (Type == rhs.Type) && (Id == rhs.Id);
    }

    Y_SAVELOAD_DEFINE(Type, Id);
    SAVELOAD(Type, Id);
};
