#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class

////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction(std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
                         unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)
{
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date;
  if (buy_sell_trans)
  {
    trans_type = "Buy";
  }
  else
  {

    trans_type = "Sell";
  }
  acb = 0;
  acb_per_share = 0;
  share_balance = 0;
  cgl = 0;
  shares = number_shares;
  amount = trans_amount;
  trans_id = assigned_trans_id;
  assigned_trans_id++;
  p_next = nullptr;
}

// Destructor
// TASK 1
//
Transaction::~Transaction()
{
  std::string symbol = "0";
  day = 0;
  month = 0;
  year = 0;
  std::string trans_type = "0";
  shares = 0;
  amount = 0;
  trans_id = 0;

  // These private members have to be populated.
  acb = 0;
  acb_per_share = 0;
  share_balance = 0;
  cgl = 0;

  p_next = nullptr;
}

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<(Transaction const &other)
{
  if (get_year() < other.get_year())
  {
    return true;
  }
  else if (get_year() == other.get_year())
  {
    if (get_month() < other.get_month())
    {
      return true;
    }
    else if (get_month() == other.get_month())
    {
      if (get_day() < other.get_day())
      {
        return true;
      }
      else if (get_day() == other.get_day())
      {
        if (get_trans_id() > other.get_trans_id())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  return false;
  // if (get_year() < other.get_year())
  // {
  //   return true;
  // }
  // else if (get_year() == other.get_year())
  // {
  //   if (get_month() < other.get_month())
  //   {
  //     return true;
  //   }
  //   else if (get_month() == other.get_month())
  //   {
  //     if (get_day() < other.get_day())
  //     {
  //       return true;
  //     }
  //     else if (get_day() == other.get_day())
  //     {
  //       if (get_trans_id() > other.get_trans_id())
  //       {
  //         return true;
  //       }
  //       else
  //       {
  //         return false;
  //       }
  //     }
  //     else
  //     {
  //       return false;
  //     }
  //   }
  //   else
  //   {
  //     return false;
  //   }
  // }
  // return false;
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }
void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }
void Transaction::set_cgl(double value) { cgl = value; }
void Transaction::set_next(Transaction *p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print()
{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
            << std::setw(4) << get_symbol() << " "
            << std::setw(4) << get_day() << " "
            << std::setw(4) << get_month() << " "
            << std::setw(4) << get_year() << " ";

  if (get_trans_type())
  {
    std::cout << "  Buy  ";
  }
  else
  {
    std::cout << "  Sell ";
  }

  std::cout << std::setw(4) << get_shares() << " "
            << std::setw(10) << get_amount() << " "
            << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
            << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
            << std::setw(10) << std::setprecision(3) << get_cgl()
            << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//
// Implement the History::insert(...) function to add a node to the linked-list
// Implement the History::read_history() function to create the linked-list using the input file
// Code de-allocation of the linked-list so that there aren't any memory leaks
// Implement the History::print() function so that we can visually verify the state of the linked-list
// after its creation.
// Implement the History::sort_by_date() function so that the linked-list is re-ordered
// chronologically
// Implement the History::update_acb_cgl() function so that key financial metrics are calculated
// Implement the History::compute_cgl() function so that key financial metrics are calculated

// Constructor
// TASK 3
//
History::History()
{ // empty all member variables in private
  p_head = 0;
  // empty the linklist
  // second
}

// Destructor
// TASK 3
//
History::~History()
{ // second
  while (p_head != nullptr)
  {
    Transaction *new_pointer = p_head;

    p_head = p_head->get_next();
    delete new_pointer;
    new_pointer = nullptr;
  }
  // all variable = 0
  // all transaction indepent
}

// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history()
{
  ece150::open_file();
  while (ece150::next_trans_entry())
  {
    // std::string symbol = ece150::get_trans_symbol();
    // // Date fields.

    // unsigned int day = ece150::get_trans_day();
    // unsigned int month = ece150::get_trans_month();
    // unsigned int year = ece150::get_trans_year();
    // // Transaction type, shares and amount.
    // unsigned int shares = ece150::get_trans_shares();
    // double amount = ece150::get_trans_amount();

    Transaction *new_pointer = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(),
                                               ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(),
                                               ece150::get_trans_amount());
    this->insert(new_pointer);
  }

  ece150::close_file();
}
// insert(...): Insert transaction into linked list.
// TASK 5
// second

void History::insert(Transaction *p_new_trans)
{

  // second
  //找到结束的位置，把pnewtrans贴上去，
  if (p_head == nullptr)
  {
    p_head = p_new_trans;
  }
  else
  {
    Transaction *pointer = p_head;
    while (pointer->get_next() != nullptr)
    {
      pointer = pointer->get_next();
    }
    pointer->set_next(p_new_trans);
    // pointer->get_next() = pointer;
  }
}
// void History::push_front( double new_value ) {
// if ( p_list_head_ == nullptr ) {
// Node *p_new_node{ new Node{ new_value, nullptr } };
// p_list_head_ = p_new_node;
// } else {

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
// Adds the passed Transaction instance to the end of the linked-list of Transactions. To be defined by the
// student.
void History::sort_by_date()
{
  Transaction *new_head = p_head;
  p_head = p_head->get_next();
  new_head->set_next(nullptr);
  while (p_head != nullptr)
  {

    if (*p_head < *new_head)
    {
      Transaction *now = p_head;
      p_head = p_head->get_next();
      now->set_next(new_head);
      new_head = now;
    }
    else
    {
      Transaction *before = new_head;
      Transaction *after = new_head->get_next();
      Transaction *now = nullptr;
      while ((after != nullptr) && (*after < *p_head))
      {
        before = after;
        after = after->get_next();
      }
      if (after == nullptr)
      {
        before->set_next(p_head);
        p_head = p_head->get_next();
        before->get_next()->set_next(nullptr);
      }
      else
      {
        before->set_next(p_head);
        p_head = p_head->get_next();
        before->get_next()->set_next(after);
      }
    }
  }
  p_head = new_head;
  // Transaction* new_list = this->p_head;
  //   this->p_head = this->p_head->get_next();
  //   new_list->set_next(NULL);

  //   while (this->p_head != NULL){
  //       Transaction* traverse_h = new_list;
  //       Transaction* traverse_t = new_list->get_next();
  //       Transaction* tmp = NULL;

  //       // if head
  //       if(*this->p_head < *traverse_h){
  //           tmp = this->p_head;
  //           this->p_head = this->p_head->get_next();
  //           tmp->set_next(traverse_h);
  //           new_list = tmp;
  //           continue;
  //       }

  //       // find the right place for node
  //       while (traverse_t != NULL && *traverse_t < *this->p_head){
  //           traverse_h = traverse_t;
  //           traverse_t = traverse_t->get_next();
  //       }

  //       if (traverse_t == NULL){
  //           // insert at the end
  //           traverse_h->set_next(this->p_head);
  //           this->p_head = this->p_head->get_next();
  //           traverse_h->get_next()->set_next(NULL);

  //       }else{
  //           // insert in the middle
  //           tmp = this->p_head;
  //           this->p_head = this->p_head->get_next();
  //           tmp->set_next(traverse_t);
  //           traverse_h->set_next(tmp);
  //       }

  //   }

  //   this->p_head = new_list;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl()
{
  Transaction *new_ACB_pointer = p_head;
  double new_acb{0};
  double new_shares{0};
  double new_shareballance{0};
  double price{0};

  while (new_ACB_pointer != NULL)
  {
    if (new_ACB_pointer->get_trans_type())
    {

      new_ACB_pointer->set_acb(new_acb + new_ACB_pointer->get_amount());
      new_acb += (new_ACB_pointer->get_amount());
      new_shares += (new_ACB_pointer->get_shares());
      new_shareballance += (new_ACB_pointer->get_shares());
      new_ACB_pointer->set_acb_per_share(new_acb / new_shares);
      new_ACB_pointer->set_share_balance(new_shareballance);
      price = new_acb / double(new_shares);
    }
    else
    {
      new_ACB_pointer->set_acb(new_acb - new_ACB_pointer->get_shares() * price);
      new_acb -= (new_ACB_pointer->get_shares() * price);
      new_shares -= (new_ACB_pointer->get_shares());
      new_ACB_pointer->set_acb_per_share(price);
      new_shareballance -= (new_ACB_pointer->get_shares());
      new_ACB_pointer->set_share_balance(new_shareballance);
      new_ACB_pointer->set_cgl(new_ACB_pointer->get_amount() - (new_ACB_pointer->get_shares() * price));
    }
    new_ACB_pointer = new_ACB_pointer->get_next();
  }
}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8

double History::compute_cgl(unsigned int year)
{
  Transaction *comcgl = p_head;
  double price{0};
  double new_cgl{0};
  double total_cgl{0};

  while (comcgl != NULL)
  {
    if (comcgl->get_year() == year)
    {
      if (comcgl->get_trans_type())
      {
        price = comcgl->get_acb_per_share();
      }
      else
      {
        new_cgl = (comcgl->get_amount() - (comcgl->get_shares() * price));
        comcgl->set_cgl(new_cgl);
        // std::cout << new_cgl << std::endl;
        total_cgl += new_cgl;
      }
    }
    comcgl = comcgl->get_next();
  }
  return total_cgl;
}
// print() Print the transaction history.
// TASK 9
//
void History::print()
{
  Transaction *data = p_head;
  std::cout << "========== BEGIN TRANSACTION HISTORY ============\n";
  while (data != nullptr)
  {
    data->print();
    data = data->get_next();
    // std::cout << "test" << std::endl;
  }
  std::cout << "========== END TRANSACTION HISTORY ============\n";
}

// GIVEN
// get_p_head(): Full access to the linked list.
// second
Transaction *History::get_p_head()
{
  return p_head;
}
