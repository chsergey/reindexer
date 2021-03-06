#pragma once

#include "core/index/index.h"
#include "core/index/string_map.h"

namespace reindexer {

template <typename T>
class IndexStore : public Index {
public:
	using Index::Index;

	KeyRef Upsert(const KeyRef &key, IdType id) override;
	void Delete(const KeyRef &key, IdType id) override;
	void DumpKeys() override {}
	SelectKeyResults SelectKey(const KeyValues &keys, CondType condition, SortType stype, ResultType res_type) override;
	void Commit(const CommitContext &) override;
	void UpdateSortedIds(const UpdateSortedContext & /*ctx*/) override {}
	Index *Clone() override;
	IdSetRef Find(const KeyRef & /*key*/) override {
		// can't
		return IdSetRef();
	}

protected:
	unordered_str_map<int>::iterator find(const KeyRef &key);
	unordered_str_map<int> str_map;
	vector<T> idx_data;

	key_string tmpKeyVal_ = make_key_string();
};

}  // namespace reindexer
