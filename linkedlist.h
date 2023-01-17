#pragma once


template<class t>
class linkedlist
{
public:
	t* data;
	linkedlist<t>* next;

	linkedlist()
	{
		data = NULL;
		next = NULL;
	}

	linkedlist(const t& value)//create copy
	{
		data = new t(value);
		if (data == NULL)
			throw - 1;
		next = NULL;
	}

	linkedlist(t* address)//already existing
	{
		data = address;
		next = NULL;
	}

	linkedlist(const linkedlist<t>& cpy)
	{
		linkedlist* currthis, * currthat;
		data = NULL;
		next == NULL;

		if (cpy.data == NULL)
			return;

		currthis = this;
		currthat = &cpy;

		while (currthat)
		{
			currthis->data = new t(currthat->data);
			if (currthis == NULL)
			{
				delete this;
				throw - 1;
			}
			currthis->next = new linkedlist();
			if (currthis->next == NULL)
			{
				delete this;
				throw - 1;
			}

			currthis = currthis->next;
			currthat = currthat->next;
		}

		
	}

	~linkedlist()
	{
		delete data;
		delete next;
	}
};

