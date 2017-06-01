#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue_simulation.h"
void main()
{
	int duration;
	// srand(time(NULL));
	while (current_time < MAX_SIMUL_TIME) {
		printf("\n----- time %d ----- \n", current_time);
		// �� job�� ������ ť�� ����
		if (is_job_arrived()) {
			++new_job_id;
			duration = get_random_duration();
			insert_job(new_job_id, current_time, duration);
		}
		// �����Ͱ� ��� ������ ���� job�� ����
		if (is_printer_idle()) {
			if (!is_PQ_empty()) process_next_job();
		}
		// ���� ����Ʈ ���̸�, ���� job�� remaining time�� �ϳ� ����
		else {
			printf(" ���� Jop <%d>�� ����Ʈ�ϰ� �ֽ��ϴ� ... \n", current_job_id);
			--remaining_time;
		}
		// ���� ť�� ���¸� ������
		PQ_show();
		++current_time;
	}
	// MAX_TIME�� ���� �� ��� �ڷ� ���
	printf("\n�Ϸ�� ����Ʈ job = %d �� \n", num_printed_jobs);
	printf("��� ���� �ð� = %f �����ð� \n\n", (double)total_wait_time / num_printed_jobs);
}

// ID�� id, ��û�ð��� arrival_time, ����Ʈ �ð��� duration�� Job�� ť�� ����
void insert_job(int id, int arrival_time, int duration)
{
	Job p;
	p.key = duration;
	// p.key = 1;
	p.id = id;
	p.arrival_time = arrival_time;
	p.duration = duration;
	insert_PQ(p);
	printf(" �� jop <%d>�� ��� �Խ��ϴ�. ����Ʈ �ð��� = %d �Դϴ�. \n", id, duration);
}

// ���� job�� ť���� ���� ����(���� job id, remaining time �� ����)
void process_next_job()
{
	Job p;
	p = delete_PQ();
	// Set global variables
	current_job_id = p.id;
	remaining_time = p.duration - 1;
	total_wait_time += current_time - p.arrival_time;
	++num_printed_jobs;
	printf(" ����Ʈ�� �����մϴ� - jop <%d>... \n", current_job_id);
}

// �����ϰ� true Ȥ�� false. True�� Ȯ���� ARRIVAL_PROB
boolean is_job_arrived()
{
	if (random() < JOB_ARRIVAL_PROB)
		return true;
	else
		return false;
}
// �����Ͱ� ��� ������(���� job�� remaining time <= 0) true
boolean is_printer_idle()
{
	if (remaining_time <= 0)
		return true;
	else
		return false;
}

// 0.0 - 1.0 ������ ���� ���� ��ȯ
double random()
{
	return rand() / (double)RAND_MAX;
}
// 1 - MAX_PRINTING_TIME+1 ������ ���� ���� ��ȯ
int get_random_duration()
{
	return (int)(MAX_PRINTING_TIME * random()) + 1;
}

void insert_PQ(Element item)
{
	int i = ++PQ_size;

	while ((i != 1) && (item.key < PQ[i / 2].key))
	{
		PQ[i] = PQ[i / 2];
		i = i / 2;
	}

	PQ[i] = item;
}

Element delete_PQ()
{
	Element min = PQ[1];
	Element temp = PQ[PQ_size--];
	int p = 1, c = 2;
	while (c <= PQ_size)
	{
		if ((c < PQ_size) && (PQ[c].key > PQ[c + 1].key))
			c++;
		if (temp.key <= PQ[c].key)
			break;
		PQ[p] = PQ[c];
		p = c;
		c = c * 2;
	}
	PQ[p] = temp;
	return min;
}

void PQ_show()
{
	printf("���� ������ ť: [ ");
	for (int i = 1; i < PQ_size + 1; i++)
	{
		printf("<%d %d> ", PQ[i].key, PQ[i].id);
	}
	printf(" ]\n");

}

boolean is_PQ_empty()
{
	if (PQ_size == 0)
		return true;
	else
		return false;
}