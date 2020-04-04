#if 1
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>


using namespace std;

//����ѧ����Ϣ��ͬ�����ʹ�ýṹ����
class student {
public:
	student(int id, string name, int score, string remark) :id(id), name(name), score(score), remark(remark) {
	}

	void print() const {
		cout << "id:" << id << " name:" << name << " score:" << score << endl;
	}
	int id;
	string name;
	int score;
	string remark;
};

// ���Ҫ��studentĳ�������ֶ�����Ϊ�������棬����Ҫ������������Ŀսṹ�����
struct _id {};
struct _name{};
struct _score {};

// ����һ��multi_index_container��������������
using student_table =
boost::multi_index::multi_index_container<
	student,
	boost::multi_index::indexed_by<
		boost::multi_index::ordered_unique<boost::multi_index::tag<_id>, BOOST_MULTI_INDEX_MEMBER(student, int, id)>,   // IDΪΨһ��������������
		boost::multi_index::ordered_non_unique<boost::multi_index::tag<_name>, BOOST_MULTI_INDEX_MEMBER(student, string, name)>, // ��Ψһ����
		boost::multi_index::ordered_non_unique<boost::multi_index::tag<_score>, BOOST_MULTI_INDEX_MEMBER(student, int, score)>
	>
>;

int main() {
	// initialize data.
	student_table allStu;
	allStu.insert(student(1, "lili", 85, "hello"));
	allStu.insert(student(2, "liming", 90, "hello"));
	allStu.insert(student(3, "xiaoming", 65, "hello"));
	allStu.insert(student(4, "ergou", 80, "hello"));
	allStu.insert(student(5, "dagou", 60, "hello"));

	// sort
	student_table::index<_id>::type& sort_id = allStu.get<0>();
	cout << "sort by student id:" << endl;
	student_table::index<_id>::type::iterator iter_id = sort_id.begin();
	for (; iter_id != sort_id.end(); iter_id++) {
		iter_id->print();
	}
	cout << "\n" << endl;

	student_table::index<_name>::type& sort_name = allStu.get<1>();
	cout << "sort by student name:" << endl;
	student_table::index<_name>::type::iterator iter_name = sort_name.begin();
	for (; iter_name != sort_name.end(); iter_name++) {
		iter_name->print();
	}
	cout << "\n" << endl;

	student_table::index<_score>::type& sort_score = allStu.get<2>();
	cout << "sort by student score:" << endl;
	student_table::index<_score>::type::iterator iter_score = sort_score.begin();
	for (; iter_score != sort_score.end(); iter_score++) {
		iter_score->print();
	}
	cout << "\n" << endl;

	// find
	student_table::index<_name>::type& find_name = allStu.get<_name>();
	student_table::index<_name>::type::iterator iter_ergou = find_name.find("ergou");
	if (iter_ergou != find_name.end()) {
		cout << "find a student named ergou:" << endl;
		iter_ergou->print();
		// modify ergou
		student ergou = *iter_ergou;
		ergou.id = 6;            // will be success. becasuse id 6 not in the table. otherwise failure
		ergou.name = "ergou_v2";
		ergou.score = 91;
		ergou.remark = "hello ergou";
		bool isSuc = find_name.replace(iter_ergou, ergou);
	}
	// 
	cout << "sort by student id after replace ergou:" << endl;
	student_table::index<_id>::type::iterator iter_id_v2 = sort_id.begin();
	for (; iter_id_v2 != sort_id.end(); iter_id_v2++) {
		iter_id_v2->print();
	}
	cout << "\n" << endl;

	system("pause");
}

#else

#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <cstdio>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using boost::multi_index_container;
using namespace boost::multi_index;
using namespace std;
using namespace boost;

// �����Ϣ
class CPlayer
{
public:
	CPlayer(int id, string name, int fight, int gold) :id(id), name(name), fight(fight), gold(gold)
	{
	}
	void print() const
	{
		cout << "id:" << id << ", name:" << name << ", fight:" << fight << ", gold:" << gold << endl;
	}

	int		id;		// Ψһid
	string	name;	// ����
	int		fight;	// ս����
	int		gold;	// ���
};

//Ҫ����CPlayer�е�ĳ�������ֶ��趨Ϊ������趨����������ֶ�ͬ���ĿյĽṹ��
struct id {};
struct name {};
struct fight {};
struct gold {};

// BOOST_MULTI_INDEX_MEMBER�� (�������е�Ԫ�ؽṹ������, ���������ͣ� ���������� ���� tag<> ���趨������)

// ����һ����������������
typedef multi_index_container
<
	CPlayer, // Ҫ��ʲô��Ϊ�������Ԫ�أ�����ýṹ������
	indexed_by
	<
	ordered_unique<tag<id>, BOOST_MULTI_INDEX_MEMBER(CPlayer, int, id)>,		// idΪΨһ���������������һһӳ�䣬 tag<����ոն���õ� struct id{} ��Ӧ������,�������ݿ�������
	ordered_non_unique<tag<name>, BOOST_MULTI_INDEX_MEMBER(CPlayer, string, name)>,	// nameΪ��Ψһ����������
	ordered_non_unique<tag<fight>, BOOST_MULTI_INDEX_MEMBER(CPlayer, int, fight)>,		// fightΪ��Ψһ����������
	ordered_non_unique<tag<gold>, BOOST_MULTI_INDEX_MEMBER(CPlayer, int, gold)>		// goldΪ��Ψһ����������
	>
>player_table;


int main()
{
	// ���е����
	player_table allPlayer;
	allPlayer.insert(CPlayer(1, "zhao", 90, 1000));	// ��
	allPlayer.insert(CPlayer(5, "qian", 80, 500));	// Ǯ
	allPlayer.insert(CPlayer(8, "sun", 100, 800));	// ��
	allPlayer.insert(CPlayer(4, "li", 90, 2500));		// ��
	allPlayer.insert(CPlayer(2, "zhou", 20, 1200));	// ��
	allPlayer.insert(CPlayer(3, "wu", 60, 1000));		// ��
	allPlayer.insert(CPlayer(7, "zheng", 40, 700));	// ֣
	allPlayer.insert(CPlayer(6, "wang", 100, 800));	// ��

													///////////////////////////////////////////////////////			����			////////////////////////////////////////////////////////
													// ʹ��get<index>�����õ������ͼ���俽�����캯���Ǳ������ģ�����ֻ�ܷ�������
													// ���ǣ������index�Ƕ�������ʱ��˳�򣬶����ǽṹ�����ֶζ����˳�򣬴�0��ʼ������3��Ӧ��gold����
	player_table::index<gold>::type& player_gold = allPlayer.get<3>();
	cout << "��gold��������Ľ��" << endl;
	player_table::index<gold>::type::iterator iter_gold = player_gold.begin();
	for (; iter_gold != player_gold.end(); iter_gold++)
	{
		iter_gold->print();
	}
	cout << "\n" << endl;

	// �õ���id��������������ͼ����ͼ��������,��ͼ�����Ǳ��һ��ӳ��,��ϵͳ�в���Ϊ��ͼ�е�Ԫ���ṩʵ�ʵĴ洢�ռ�,�����ڶ���ʵ���ָ������ָ�룩
	player_table::index<id>::type& player_ID = allPlayer.get<id>();
	cout << "��id��������Ľ��" << endl;
	player_table::index<id>::type::iterator iter_ID = player_ID.begin();
	for (; iter_ID != player_ID.end(); iter_ID++)
	{
		iter_ID->print();
	}
	cout << "\n" << endl;

	// �õ���fight��������������ͼ
	player_table::index<fight>::type& player_fight = allPlayer.get<fight>();
	cout << "��fight��������Ľ��" << endl;
	player_table::index<fight>::type::iterator iter_score = player_fight.begin();
	for (; iter_score != player_fight.end(); iter_score++)
	{
		iter_score->print();
	}
	cout << "\n" << endl;

	// ����gold��[1000-2000]֮������
	cout << "����gold��1000-2000֮������" << endl;
	player_table::index<gold>::type::iterator iter_low = allPlayer.get<gold>().lower_bound(1000);
	player_table::index<gold>::type::iterator iter_up = allPlayer.get<gold>().upper_bound(2000);
	while (iter_low != iter_up)
	{
		iter_low->print();
		iter_low++;
	}
	cout << "\n" << endl;

	///////////////////////////////////////////////////////			����			////////////////////////////////////////////////////////
	// insert() ��������std::pair<iterator,bool>�ԣ��ɹ�ʱ��iteratorָ��ɹ�����Ķ���boolΪtrue;ʧ��ʱiteratorָ��֮ǰ�Ѵ��ڵĶ���boolΪfalse
	// �ɹ���
	bool bSuc = allPlayer.insert(CPlayer(9, "zheng", 200, 2000)).second;// ֣
	cout << "����ɹ����ֵ��" << bSuc << endl;
	// ʧ�ܣ���ΪIDΪ9���Ѵ��ڣ���
	bSuc = allPlayer.insert(CPlayer(9, "zheng2", 300, 1000)).second;// ֣2
	cout << "����ʧ�ܽ��ֵ��" << bSuc << endl;
	cout << "\n" << endl;

	///////////////////////////////////////////////////////			����			////////////////////////////////////////////////////////
	// �õ���name��������������ͼ,��ִ��find()����
	cout << "����zhou" << endl;
	player_table::index<name>::type::iterator iter_name = allPlayer.get<name>().find("zhou");
	if (iter_name != allPlayer.get<name>().end())
	{
		cout << "find zhou player!" << endl;
		iter_name->print();
	}
	else
	{
		cout << "cant't find zhou player!" << endl;
	}

	///////////////////////////////////////////////////////			replace()�޸�			////////////////////////////////////////////////////////
	player_table::index<name>::type& player_name = allPlayer.get<name>();
	// �ɹ���replace()
	player_table::index<name>::type::iterator iter_wang = player_name.find("wang"); // ����wang
	if (iter_wang != player_name.end())
	{
		cout << "�ҵ�wang���������" << endl;
		iter_wang->print();

		CPlayer wang = *iter_wang;
		wang.gold = 1000;
		wang.id = 66;	  // ����id��Ψһ�ģ���66�����ڣ��޸ĺ�replace�᷵�سɹ�
		bSuc = player_name.replace(iter_wang, wang);
		cout << "�޸�wang��idΪ66�Ľ��ֵ��" << bSuc << endl;
	}
	// ʧ�ܵ�replace()
	iter_wang = player_name.find("wang"); // ���²���wang
	if (iter_wang != player_name.end())
	{
		cout << "�����ҵ�wang���������" << endl;
		iter_wang->print();

		CPlayer wang = *iter_wang;
		wang.gold = 1000;
		wang.id = 1;	  // ����id��Ψһ�ģ���1�Ѵ��ڣ��޸ĺ�replace�᷵��ʧ�ܣ���ʱreplace���Ա�֤�������ᷢ���κα仯
		bSuc = player_name.replace(iter_wang, wang);
		cout << "�޸�wang��idΪ1�Ľ��ֵ��" << bSuc << endl;
	}
	// ע�⣺replace()�ᷢ�����θ�ֵ����������ṹ�ܴ���ʹ�õĺ�Ƶ�����п��ܻ��Ϊ����ƿ��
	cout << "\n" << endl;

	///////////////////////////////////////////////////////			modify()�޸�			////////////////////////////////////////////////////////
	// �ȶ����޸ĵĺ��������������޸�idΪ��
	class CModifyPlayer
	{
	public:
		CModifyPlayer(int id) :m_id(id)
		{
		}
		void operator()(CPlayer& player)
		{
			player.id = m_id;
		}
	private:
		int m_id;
	};

	// �ɹ���modify()
	player_table::index<name>::type::iterator iter_zheng = player_name.find("zheng"); // ����zheng
	if (iter_zheng != player_name.end())
	{
		cout << "�ҵ�zheng���������" << endl;
		iter_zheng->print();

		// ����id��Ψһ�ģ���50�����ڣ��޸ĺ�modify�᷵�سɹ�
		bSuc = player_name.modify(iter_zheng, CModifyPlayer(50));
		cout << "�޸�zheng��idΪ50�Ľ��ֵ��" << bSuc << endl;
	}

	cout << "������name�������ͼ" << endl;
	iter_name = player_name.begin();
	for (; iter_name != player_name.end(); iter_name++)
	{
		iter_name->print();
	}

	// ʧ�ܵ�modify()
	iter_zheng = player_name.find("zheng"); // ���²���zheng
	if (iter_zheng != player_name.end())
	{
		cout << "�����ҵ�zheng���������" << endl;
		iter_zheng->print();

		// ����id��Ψһ�ģ���5�Ѿ����ڣ��޸ĺ�modify�᷵��ʧ�ܣ��ұ�Ԫ�أ�iter_zheng��Ҳ�ᱻɾ����������
		bSuc = player_name.modify(iter_zheng, CModifyPlayer(5));
		cout << "�޸�zheng��idΪ5�Ľ��ֵ��" << bSuc << endl;
	}

	cout << "�ٴα�����name�������ͼ" << endl;
	iter_name = player_name.begin();
	for (; iter_name != player_name.end(); iter_name++)
	{
		iter_name->print();
	}
	cout << "\n" << endl;

	///////////////////////////////////////////////////////			ɾ��			////////////////////////////////////////////////////////
	cout << "ɾ��idΪ2�����" << endl;
	player_table::index<id>::type::iterator iter_2 = player_ID.find(2);
	if (iter_2 != player_ID.end())
	{
		player_ID.erase(iter_2);
	}
	cout << "�ٴα�����id�������ͼ" << endl;
	iter_ID = player_ID.begin();
	for (; iter_ID != player_ID.end(); iter_ID++)
	{
		iter_ID->print();
	}
	cout << "\n" << endl;

	getchar();
	return 0;
}

#endif
