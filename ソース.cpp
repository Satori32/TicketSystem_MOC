#include <iostream>
#include <deque>
#include <cstdint>
#include <string>
#include <memory>

enum class State {
	None,
	Wait,
	End,
	NowWorking,
	Begin,
};

typedef std::intmax_t IDNumber;

struct Ticket {
	IDNumber ID = 0;
	State state=State::None;
	std::string  Text;
};

typedef std::shared_ptr<Ticket> STicket;

struct TicketSystem
{
	IDNumber Count = 0;
	std::deque<STicket> Tickets;

};

STicket New(TicketSystem& S, const Ticket& T) {
	Ticket X = T;
	X.ID = S.Count++;
	S.Tickets.push_back(std::make_shared<Ticket>(X));
	return S.Tickets.back();
}

STicket Find(TicketSystem& S, IDNumber ID) {
	for (auto& o : S.Tickets) {
		if (o->ID == ID) { return o; }
	}
	return S.Tickets.back();

}

bool Free(TicketSystem& S, IDNumber ID) {
	for (auto It = S.Tickets.begin(); It != S.Tickets.end(); It++) {
		if ((*It)->ID == ID) {
			S.Tickets.erase(It);
			return true;
		}
	}
	return false;
}

int main() {
	TicketSystem TS;

	Ticket T{};
	T.state = State::Begin;
	T.Text = "XX:XX start.";
	auto ST1 = New(TS, T);
	auto ST2 = New(TS, T);
	auto ST3 = New(TS, T);


	return 0;
}