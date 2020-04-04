/**
boost ������������һ��ʹ��
����ʹ��google ��gmock ������֤��boost ������ģ���ʹ�ã�����֤��
���������õģ����ܻ���һЩ�ַ��ô��������������ķţ��޸�һ�£�ͬʱ����gmock��Ϳ������������ˡ�
��Ȼ����Ҫ����boost ����ؿ�
**/


#include <stdint.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/global_fun.hpp>


// �������Ľṹ������
struct stru_AccountFeeIncre
{
	int64_t nAccountID;
	int32_t nGoodsID;
	int32_t nGoodsGroupID;
	int32_t nFeeMode;
	int32_t nTradeMode;
	double dFeeValue;
};

// Ϊ������Key ����һ����־���ͣ�����std::map ��Key
struct tagGoodsID {};
struct tagGoodsGroupID {};

// �����������ṹ����Ҫ���������Ϳ�����ָ����Ա��һһӳ��
using MultiIndexFeeIncre =
boost::multi_index::multi_index_container<
	stru_AccountFeeIncre,    // ���ݽṹ�����������Ķ���
	boost::multi_index::indexed_by<    // ����������������һ�����߶�����ֱ���',' �ָ�
									   // ����Ψһ�����������������ֶε�ֵ��ͬ���������󵽴������С�
	boost::multi_index::ordered_unique<
	boost::multi_index::tag<tagGoodsID>,    // ������ǩ
	BOOST_MULTI_INDEX_MEMBER(stru_AccountFeeIncre, int32_t, nGoodsID)    // �������󶨵ĳ�Ա
	>,
	// ������Ψһ��������������ͬ��ֵ����������
	boost::multi_index::ordered_non_unique<
	boost::multi_index::tag<tagGoodsGroupID>,
	BOOST_MULTI_INDEX_MEMBER(stru_AccountFeeIncre, int32_t, nGoodsGroupID)
	>
	>
>;

using C_ITER_FEE_INCRE = MultiIndexFeeIncre::const_iterator;
using PAIR_RANGE_FEE_INCRE = std::pair<C_ITER_FEE_INCRE, C_ITER_FEE_INCRE>;
using C_ITER_ID_FEE_INCRE = MultiIndexFeeIncre::index<tagGoodsID>::type::const_iterator;
using C_ITER_GROUP_FEE_INCRE = MultiIndexFeeIncre::index<tagGoodsGroupID>::type::const_iterator;
using PAIR_RANGE_GROUP_FEE_INCRE = std::pair<C_ITER_GROUP_FEE_INCRE, C_ITER_GROUP_FEE_INCRE>;

// �������������ʵ��
static MultiIndexFeeIncre s_multiAccountFeeIncre;
// ��������������ʵ�������� - ��const �汾
static MultiIndexFeeIncre::index<tagGoodsID>::type &INDEX_ID_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsID>();
static MultiIndexFeeIncre::index<tagGoodsGroupID>::type &INDEX_GROUP_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsGroupID>();
// ��������������ʵ�������� - const �汾
static const MultiIndexFeeIncre::index<tagGoodsID>::type &C_INDEX_ID_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsID>();
static const MultiIndexFeeIncre::index<tagGoodsGroupID>::type &C_INDEX_GROUP_FEE_INCRE = s_multiAccountFeeIncre.get<tagGoodsGroupID>();

// template �汾
MultiIndexFeeIncre::template index<tagGoodsID>::type &TPLT_INDEX_ID = s_multiAccountFeeIncre.template get<tagGoodsID>();
MultiIndexFeeIncre::template index<tagGoodsGroupID>::type &TPLT_INDEX_GROUP = s_multiAccountFeeIncre.template get<tagGoodsGroupID>();

TEST(TestBoostUse, MultiIndex)
{
	const int32_t GROUP_ID_01 = 1;
	const int32_t GROUP_ID_02 = 2;
	int64_t nExpectSize = 0;

	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	int64_t nGoodsID = 1;
	stru_AccountFeeIncre stFeeIncre;
	stFeeIncre.nAccountID = 1;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;
	stFeeIncre.nFeeMode = 0;
	stFeeIncre.nTradeMode = 1;
	stFeeIncre.dFeeValue = 0.5;

	// ��Ʒ��1
	int32_t nExpectSizeGroupID_1 = 0;
	// ����һ��
	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ������Ψһ������ͬ��ֵ�Ķ��󣬲���ʧ��
	s_multiAccountFeeIncre.emplace(stFeeIncre);
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ����һ��
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ����һ��
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_01;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_1;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ���뵽��һ����Ʒ��
	int32_t nExpectSizeGroupID_2 = 0;
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_02;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_2;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ����һ��
	++nGoodsID;
	stFeeIncre.nGoodsID = nGoodsID;
	stFeeIncre.nGoodsGroupID = GROUP_ID_02;

	s_multiAccountFeeIncre.emplace(stFeeIncre);
	++nExpectSize;
	++nExpectSizeGroupID_2;
	EXPECT_EQ(nExpectSize, s_multiAccountFeeIncre.size());

	// ��ѯ
	do
	{
		// Ψһ�����Ĳ�ѯ���������һ����¼
		int nTempGoodsID = 1;
		C_ITER_ID_FEE_INCRE c_iter_id = INDEX_ID_FEE_INCRE.find(nTempGoodsID);
		ASSERT_NE(c_iter_id, INDEX_ID_FEE_INCRE.end());

		// ��Ψһ�����Ĳ�ѯ�����Ϊһ���¼
		PAIR_RANGE_GROUP_FEE_INCRE range = TPLT_INDEX_GROUP.equal_range(GROUP_ID_01);
		int nTempSize = 0;
		for (auto it = range.first; it != range.second; ++it)
		{
			EXPECT_EQ(GROUP_ID_01, it->nGoodsGroupID);
			++nTempSize;
		}

		EXPECT_EQ(nExpectSizeGroupID_1, nTempSize);
	} while (false);

	// �޸�
	do
	{
		// ��������
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t nTempGoodsID = 1;

		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		EXPECT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		if (c_iter_id == bak_multiAccountFeeIncre.get<tagGoodsID>().end())
		{
			break;
		}

		stru_AccountFeeIncre newObj;    // δ����ֵʹ���ڴ����ֵ����
		newObj.nGoodsID = c_iter_id->nGoodsID; // Ψһ���������޸�
		newObj.nGoodsGroupID = nExpectSizeGroupID_2;    // ��Ʒ��ID�ĵ�2 ��Ψһ�������޸�
		bool bResTemp = bak_multiAccountFeeIncre.replace(c_iter_id, newObj);
		EXPECT_TRUE(bResTemp);
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// ��������
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t nTempGoodsID = 1;

		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		EXPECT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		if (c_iter_id == bak_multiAccountFeeIncre.get<tagGoodsID>().end())
		{
			break;
		}

		stru_AccountFeeIncre newObj;
		newObj.nGoodsID = 23487954;    // �޸�Ψһ������
		newObj.nGoodsGroupID = c_iter_id->nGoodsGroupID;    // ��Ψһ���������޸�
		bool bResTemp = bak_multiAccountFeeIncre.replace(c_iter_id, newObj);
		EXPECT_TRUE(bResTemp);
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	// ɾ��
	do
	{
		// ��������
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t bakExpectSizeGroupID_1 = nExpectSizeGroupID_1;

		// ��ɾ����Ʒ��1 �е�һ����Ʒ
		int nTempGoodsID = 1;
		C_ITER_ID_FEE_INCRE c_iter_id = bak_multiAccountFeeIncre.get<tagGoodsID>().find(nTempGoodsID);
		ASSERT_NE(c_iter_id, bak_multiAccountFeeIncre.get<tagGoodsID>().end());
		bak_multiAccountFeeIncre.erase(c_iter_id);
		--bakExpectSize;
		--bakExpectSizeGroupID_1;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());

		// ɾ����Ʒ��1 ��Ԫ��
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.get<tagGoodsID>().size());
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.get<tagGoodsGroupID>().size());
		bak_multiAccountFeeIncre.template get<tagGoodsGroupID>().erase(GROUP_ID_01);
		bakExpectSize -= bakExpectSizeGroupID_1;
		bakExpectSizeGroupID_1 = 0;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// ��������
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakExpectSize = nExpectSize;
		int32_t bakExpectSizeGroupID_2 = nExpectSizeGroupID_2;

		// ɾ����Ʒ��2 ��Ԫ��
		bak_multiAccountFeeIncre.template get<tagGoodsGroupID>().erase(GROUP_ID_02);
		bakExpectSize -= bakExpectSizeGroupID_2;
		bakExpectSizeGroupID_2 = 0;
		EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
	} while (false);

	do
	{
		// ��������
		MultiIndexFeeIncre bak_multiAccountFeeIncre = s_multiAccountFeeIncre;
		int32_t bakGoodsID = nGoodsID;
		int32_t bakExpectSize = nExpectSize;

		// ��Ψһ������: ��ƷID ����ɾ��
		do
		{
			bak_multiAccountFeeIncre.template get<tagGoodsID>().erase(bakGoodsID);
			--bakExpectSize;
			EXPECT_EQ(bakExpectSize, bak_multiAccountFeeIncre.size());
		} while (--bakGoodsID > 0);
	} while (false);
}


int main(int argc, char *argv[])
{
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}