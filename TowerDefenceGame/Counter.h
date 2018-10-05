#pragma once

class Counter {
public:
	Counter() {
		m_count = 0;
	}
	virtual ~Counter() {}

	virtual void update() {
		m_count++;
	}
	long long getCount() const {
		return this->m_count;
	}
	
	void setCount(long long count) { m_count = count; }
	void reset() { this->m_count = 0; }

protected:
	long long m_count;

};

class LimitedCounter : public Counter {
public:
	LimitedCounter(long long max) {
		m_max = max;
	}
	~LimitedCounter() {}

	void update() override {
		if (m_count == m_max)return;
		m_count++;
	}
	bool isLimit() const { return this->m_count == m_max; }

protected:
	long long m_max;
};