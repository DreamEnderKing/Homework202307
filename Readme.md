# ѧ���ɼ�����ϵͳ�����
====

���ߣ���������24��2022010606

## Ŀ¼

1.[ϵͳ�������](#ϵͳ�������)

2.[�������](#�������)

3.[��ϸ���](#��ϸ���)

4.[ϵͳ����](#ϵͳ����)

5.[�������](#�������)

6.[�ܽ�](#�ܽ�)

## ϵͳ�������
----

�ɼ�����ϵͳ����ȫ�淴ӳ��ѧ���μӿ��ԵĿγ���ź���Ӧ�ĳɼ��������Ҫ�ṩ���¹��ܣ�

### 1.¼�빦�ܣ�
ͨ�������¼��������ÿ�ſγ�ͳһ�ĳɼ�����ʽ���֣��ɼ�����ϵͳӦ��֧������¼�뷽ʽ��

A���ļ�¼�룺ֱ�ӻ�ȡ�����ļ�·��������Լ����ʽ���ж�ȡ
B�������룺�ȶ�ȡ�γ����ƣ�Ȼ���cin���������ȡ����

### 2.�޸Ĺ��ܣ�
֧���޸�ѧ���ɼ�

### 3.��ѯ���ܣ�
֧�ֲ�ѯѧ�������ɼ�������ɼ���Ҳ֧�ֲ�ѯ����γ������ɼ��������ͳ�����ݡ�ͳ������Ӧ��֧�����������ʽ��

A���ɼ�������������ʽΪ���γ�����+�ɼ�+����ͳ�����ݡ������˶ˣ�/��ѧ��id+�ɼ�+����ͳ�����ݡ�

B�����ݱ�����������ʽΪ���γ�/ѧ��id+�ɼ���

### 4.ͳ�ƹ��ܣ�
֧��ͳ��ƽ��ѧ�ּ������Ƴɼ���ָ����ĳ�����ڵ�ѧ��id

## �������
----

�ɼ�����ϵͳ����4��ܣ�¼�롢�޸ġ���ѯ��ͳ�ơ�

### ¼��
��¼��ʱ�û�����ѡ��ֱ�Ӹ����ļ�·�������ļ���һ��Ϊ���ÿγ�ID ����Name ѧ��Point����ʣ����Ϊѧ���ɼ����ݣ���ʽΪ��ѧ��ID �ɼ�����Ҳ�������ֶ�����γ���Ϣ��Ȼ������ѧ���ɼ����ݣ���������������Լ��ʱ���Զ��������ݣ��������븺��ID�����ɼ�ʱ�˳�����ģʽ��������ͬ�����ڴ��е����ݿ⡣

### �޸�

�޸�ʱ�û���Ҫ�ṩ�γ̺�ID��ѧ��ID�������жϿγ��Ƿ���ڣ����������򲵻ز�������֤�γ�����ֻ��ͨ��¼�벽����С�Ȼ���ж�ѧ��ID�Ƿ���ڣ����������޸�ѧ���ɼ���������ʾ�Ƿ������µ�������Ŀ�����ȷ�����ӣ�������ѧ���ɼ���Ŀ������������ɺ󽫶��ڴ��е����ݿ�������Ӧ�ĸĶ���

### ��ѯ

��ѯ��֧Ϊ2����x2��ʾ����ϣ�����Ϊ����ѯѧ�����˳ɼ�/��ѯ���ſγ̳ɼ�����ʾΪ�����Ի��Ű�+ͳ������/���ݱ���ʽ��
��ѯʱ�û�������Ҫ�ṩѧ��/�γ�ID��ȷ�����ݴ��ں���������Ӧ���ݡ����ѡ�������Ի��Ű棬��ô���򻹻����ͳ�������Ϣ������˳ɼ���ƽ��ѧ�ּ�����ѧ�ֺͿγ̳ɼ���ƽ���֡����/�ͷּ�������

### ͳ��

ͳ������ͳ��ѧ�ּ���ĳ��������ѧ���ļ��ϣ�����ѡ������ѧ��/����ѧ������ģʽ��ѡ�����ʱ��Ҫ�����ṩ�γ�ID���ڸ�������˵�(-1�����޶˵�)�󣬳�������ڸ�������ѧ����ID�ͳɼ���Ϣ��

## ��ϸ���
----

����ǰ��˽��з��롣���������ݴ�����������������(ClassInfo, StudentInfo��ClassData)���������ݽṹ��(StudentBriefData, ModifyLog��ClassItem)������������Structure.h��(Structure�����ռ���)������ǰ���û�������Ϊ5����������Ӧ�����¼�롢�޸ġ���ѯ��ͳ���Ĵ��ܣ���������Displayer.h��(Displayer�����ռ���)������ͨ��main()��ά����ΨһClassInfoʵ�����н�����

Structure����ͽṹ����ͼΪ��

![Structure���ͼ](doc/img0.png)

### �����ࣺ

#### `ClassInfo`

��Displayer.h���û�չʾ���������Ľӿڣ�ͼʾ���£� 	

![ClassInfoͼ����ʾ����](doc/img1.png)

#### `StudentInfo`

ѧ�����ݿ⣬ͬʱ�����޸ĺ��ClassData��ʱ�ϲ���ά����ѧ��ƽ��ѧ�ּ���ͳ�������С�

![StudentInfoͼ����ʾ����](doc/img2.png)

#### `ClassData`

���ſγ����ݽṹ�������γ������Ϣ��ѧ�����ݿ⣬ͬʱά���޸ļ�¼������ʡȥ��ν��ȫ�ֱȽϹ��̡�

![ClassDataͼ����ʾ����](doc/img3.png)

### ���ݽṹ�壺

#### `StudentBriefData`

���õĵ���ѧ��ͳ�����ݣ���Ա��ƽ���ɼ�(`float averageScore`),��ѧ��(`int totalPoint`)

#### `ModifyLog`

�����޸ļ�¼����Ա���޸�״̬(`ModifyStatus status`),ѧ��ID(`int stuID`),�ɼ�(`int score`),֮ǰ�ɼ�(`int oldScore`,����`status==Modified`ʱ��Ч)��

#### `ClassItem`

����ɼ�����Ա���γ�ID(`int ID`),�γ�����(`string Name`),�ɼ�(`int Point`),ѧ��(`int ClassPoint`)

### �û���������

��������`main()`��ά�ֱ���`branch`���ڲ�ͬ�Ľ��棬�û�ѡ��ͬ�Ĳ������û����������᷵��`int`ֵ����������`int`ֵд��`branch`����������ֵѡ����һ��Ҫʹ�õ��û��������������û�������������ʱ����������������Ϣ���ص���Ļ����ʱ`branch`ֵ���䣬������ֹͣ2s������ִ��ͬһ�û�����������

## ϵͳ����
----

�����д��Ϻ��ҽ��뵽�˳�����Խ׶Ρ�����һ�׶Σ�������������Ҫ�����¼��㣺

1.����Ԥ���Ľӿڲ�����һ���棬��ϣ����������������Ϊ`protected`�Է�ֹ�����޸ģ���һ���棬���ֲ����漰��������Ը����ڲ����ݵ��޸ġ��ڵ�һ���У���ʹ����`friend`����������ô�����ɻ��ƻ���ķ�װ�ԡ�����`ClassInfo`��Ҫ�޸�`StudentInfo`���ݣ���ζ��`StudentInfo`����Ӧ���ں��棬����`friend`���벻ͨ��������`StudentInfo`��һ��ʵ������`ClassInfo`��һ�������ԣ���ô֮ǰ�����о�Υ�����߼�˳������ڵڶ������ҽ����޸ĳ���ר�õ�`Get/Update/Join`�����������������˷��������������Ǻܺõ�ά������ķ�װ�ԣ��������뵽�����Žⷨ����ʱ��ͺܿ���֮ǰԤ���Ľӿ������ˣ��κ�һ�����ܸĶ����п�����Ҫһ���µĽӿڣ�����Ҳ�Ǿ��鲻���Ե�ʡ�

2.�쳣�����ܼ��֡�����˳��˼·���б�̣����Ե��˿��ܳ��ֵ��쳣�����`cin >> (int)i`����ô�û������˷�`int`������ô�죿`map.find()`����û�ҵ���ô�죿`ifstream file(...)`���ļ�û����������ô�죿��Щ��ʵ�ʵı���зǳ��������ǣ����ҳ������ⲻһ����ʵ�ʳ���bug�ĵط���������������֮��ų�������δ��֤�������Ĵ������bug���޸������˺ܴ���鷳��Ҳ��ʾ��Ӧ��ʱʱ�̿�ע����ܳ��ֵ��쳣�����

3.���ڹ�������`std::pair`�����ʼ�������У�����һ��`pair`������������񣬵�֮����ܷ��ִ洢��������Ϣ��������ʱ�ͳ����˼������������`pair`�ڲ�Ƕ��`pair`�����������Ϊֹ��`StudentInfo`����Ȼ�������������`map`����ʱ��������`i->second.second`�������������������д������һ�����ѡ��ں����޸��У��ҽ��������������ݽṹ�壬������`pair`��ʹ��������ϧֱ�������д������ŷ���C++ 11֧��`tuple`���������ݽṹ��Ҳ���ã��������Űɡ�

4.`const`������������ʵ�ʱ���к���ʹ�á��ڿγ�ѧϰ�У�`const`���������;���һ�����ѵ㣬����ʵ�ʱ���У�����������ʹ�����������ܼ�ǿ���﷨�����ͽ����һЩ��������ĸ��Ʋ�����ͬʱ��`const`�β�Ҳʹ��ĳЩSTL��������ͨ����������޸ı������ܴ��뺯�����д������������Ǻܵ�Ч�ģ�������������Щ������������Ҫ�����Ķ����룬Ū������������Ķ�����Щ���������Է�����

������Ժ�bug��Ȼ���ڣ������޸�bug�Ĺ����У���Ҳ�ջ��˲��١�

## �������
----

��һ�����лᵯ����ʼ�����������棬�����û�ָ����·���������ݿ⣬���ҽ���·��д�뵽ע����С�ע���·��Ϊ��

`HKEY_CURRENT_USER\Software\DreamEnderKing\Project2023Summer\path`

���������ļ�λ��test�ļ����£����临�Ƶ�E:\bin�ļ�����������������

����Ϊ���н�ͼ��


#### `int Cover(Structure::ClassInfo& info)`

![Cover()ͼ����ʾ����](doc/img4.png)


#### `int Input(Structure::ClassInfo& info)`

![Input()ͼ����ʾ����](doc/img5.png)

#### `int Modify(Structure::ClassInfo& info)`

![Modify()ͼ����ʾ����](doc/img6.png)

#### `int Search(Structure::ClassInfo& info)`

![Search()ͼ����ʾ����](doc/img7.png)

#### `int Count(Structure::ClassInfo& info)`

![Count()ͼ����ʾ����](doc/img8.png)

����˵˵����Ŀǰ�Ĳ���ɡ�

1.Ŀǰ����ָ��ֻ����E:\bin�ļ����¹�����û�е�һ������ʱ��������

2.ÿ�δ򿪶���������ͳ�ƣ��޷�׼ȷУ���û��Ƿ��ڳ������޸��������ļ���

3.������ͣʹ���˴���sleep()������ʵ�ǲ����õģ��ڽ������ĸĶ��н����滻Ϊsystem("pause")��������Ի��Ľ��������

## �ܽ�
----

����γ�������У���ѧ���˴���C++ STL���֪ʶ��Ҳ��ʶ����C++ STL����Ͻ��Ժ͹㷺�ԡ�������ģ��Ӧ�ã�ʹ��STL�����Խ��ٵĴ���ʵ�ּ�Ϊǿ��Ĺ��ܡ�