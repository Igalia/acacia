%module acacia_ia2
%{
#include <include/acacia/ia2/ia_2.h>
#include <include/acacia/ia2/ia_action.h>
#include <include/acacia/ia2/ia_component.h>
#include <include/acacia/ia2/ia_hyperlink.h>
#include <include/acacia/ia2/ia_node.h>
#include <include/acacia/ia2/ia_table2.h>
#include <include/acacia/ia2/ia_table_cell.h>
#include <include/acacia/ia2/ia_text.h>
#include <include/acacia/ia2/ia_value.h>

using namespace acacia;
%}

%include <std_pair.i>
%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(StringVector) vector<string>;
  %template(PairLongLong) pair<long, long>;
};

%catches(std::runtime_error) acacia::IANode::getAccRole();
%catches(std::runtime_error) acacia::IANode::getAccName();
%catches(std::runtime_error) acacia::IANode::getAccDescription();
%catches(std::runtime_error) acacia::IANode::getAccChildCount();
%catches(std::runtime_error) acacia::IANode::getAccState();
%catches(std::runtime_error) acacia::IANode::AccessibleChildAt(int index);
%catches(std::runtime_error) acacia::IANode::getStateStrings();
%catches(std::runtime_error) acacia::IANode::QueryIA2();
%catches(std::runtime_error) acacia::IANode::QueryAction();
%catches(std::runtime_error) acacia::IANode::QueryComponent();
%catches(std::runtime_error) acacia::IANode::QueryHypertext();
%catches(std::runtime_error) acacia::IANode::QueryTable2();
%catches(std::runtime_error) acacia::IANode::QueryTableCell();
%catches(std::runtime_error) acacia::IANode::QueryText();
%catches(std::runtime_error) acacia::IANode::QueryValue();

%catches(std::runtime_error) acacia::IA2::isNull();
%catches(std::runtime_error) acacia::IA2::getAttributes();
%catches(std::runtime_error) acacia::IA2::getGroupPosition();
%catches(std::runtime_error) acacia::IA2::role();
%catches(std::runtime_error) acacia::IA2::getStates();
%catches(std::runtime_error) acacia::IA2::toString();
%catches(std::runtime_error) acacia::IA2::getRelations();
%catches(std::runtime_error) acacia::IA2::getStateStrings();

%catches(std::runtime_error) acacia::IAAction::isNull();
%catches(std::runtime_error) acacia::IAAction::nActions();
%catches(std::runtime_error) acacia::IAAction::getDescription(int index);
%catches(std::runtime_error) acacia::IAAction::getName(int index);
%catches(std::runtime_error) acacia::IAAction::toString();

%catches(std::runtime_error) acacia::IAComponent::isNull();
%catches(std::runtime_error) acacia::IAComponent::getBackground();
%catches(std::runtime_error) acacia::IAComponent::getForeground();
%catches(std::runtime_error) acacia::IAComponent::getLocationInParent();
%catches(std::runtime_error) acacia::IAComponent::toString();

%catches(std::runtime_error) acacia::IAHyperlink::isNull();
%catches(std::runtime_error) acacia::IAHyperlink::getStartIndex();
%catches(std::runtime_error) acacia::IAHyperlink::getEndIndex();
%catches(std::runtime_error) acacia::IAHyperlink::getAnchorTarget(long index);
%catches(std::runtime_error) acacia::IAHyperlink::toString();

%catches(std::runtime_error) acacia::IATable2::isNull();
%catches(std::runtime_error) acacia::IATable2::getNColumns();
%catches(std::runtime_error) acacia::IATable2::getNRows();
%catches(std::runtime_error) acacia::IATable2::toString();

%catches(std::runtime_error) acacia::IATableCell::isNull();
%catches(std::runtime_error) acacia::IATableCell::getColumnExtent();
%catches(std::runtime_error) acacia::IATableCell::getColumnIndex();
%catches(std::runtime_error) acacia::IATableCell::getRowExtent();
%catches(std::runtime_error) acacia::IATableCell::getRowIndex();
%catches(std::runtime_error) acacia::IATableCell::toString();

%catches(std::runtime_error) acacia::IAText::isNull();
%catches(std::runtime_error) acacia::IAText::getCaretOffset();
%catches(std::runtime_error) acacia::IAText::getNCharacters();
%catches(std::runtime_error) acacia::IAText::getText(long start_offset, long end_offset);
%catches(std::runtime_error) acacia::IAText::toString();

%catches(std::runtime_error) acacia::IAValue::isNull();
%catches(std::runtime_error) acacia::IAValue::getCurrentValue();
%catches(std::runtime_error) acacia::IAValue::getMaximumValue();
%catches(std::runtime_error) acacia::IAValue::getMinimumValue();
%catches(std::runtime_error) acacia::IAValue::toString();

#define ACACIA_EXPORT
%include <acacia/ia2/ia_2.h>
%include <acacia/ia2/ia_action.h>
%include <acacia/ia2/ia_component.h>
%include <acacia/ia2/ia_hyperlink.h>
%include <acacia/ia2/ia_table2.h>
%include <acacia/ia2/ia_table_cell.h>
%include <acacia/ia2/ia_text.h>
%include <acacia/ia2/ia_value.h>
%include <acacia/ia2/ia_node.h>

%rename(findRootIANodeForPID) acacia::findRootIANodeForPID;
%rename(findRootIANodeForName) acacia::findRootIANodeForName;
