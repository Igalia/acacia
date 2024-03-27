%module ia2_inspect
%{
#include <include/axaccess/ia2/ia_2.h>
#include <include/axaccess/ia2/ia_action.h>
#include <include/axaccess/ia2/ia_component.h>
#include <include/axaccess/ia2/ia_hyperlink.h>
#include <include/axaccess/ia2/ia_node.h>
#include <include/axaccess/ia2/ia_table2.h>
#include <include/axaccess/ia2/ia_table_cell.h>
#include <include/axaccess/ia2/ia_text.h>
#include <include/axaccess/ia2/ia_value.h>
%}

%include <std_pair.i>
%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(StringVector) vector<string>;
  %template(PairLongLong) pair<long, long>;
};

%catches(std::runtime_error) IANode::getAccRole();
%catches(std::runtime_error) IANode::getAccName();
%catches(std::runtime_error) IANode::getAccDescription();
%catches(std::runtime_error) IANode::getAccChildCount();
%catches(std::runtime_error) IANode::getAccState();
%catches(std::runtime_error) IANode::AccessibleChildAt(int index);
%catches(std::runtime_error) IANode::getStateStrings();
%catches(std::runtime_error) IANode::QueryIA2();
%catches(std::runtime_error) IANode::QueryAction();
%catches(std::runtime_error) IANode::QueryComponent();
%catches(std::runtime_error) IANode::QueryHypertext();
%catches(std::runtime_error) IANode::QueryTable2();
%catches(std::runtime_error) IANode::QueryTableCell();
%catches(std::runtime_error) IANode::QueryText();
%catches(std::runtime_error) IANode::QueryValue();

%catches(std::runtime_error) IA2::isNull();
%catches(std::runtime_error) IA2::getAttributes();
%catches(std::runtime_error) IA2::getGroupPosition();
%catches(std::runtime_error) IA2::role();
%catches(std::runtime_error) IA2::getStates();
%catches(std::runtime_error) IA2::toString();
%catches(std::runtime_error) IA2::getRelations();
%catches(std::runtime_error) IA2::getStateStrings();

%catches(std::runtime_error) IAAction::isNull();
%catches(std::runtime_error) IAAction::nActions();
%catches(std::runtime_error) IAAction::getDescription(int index);
%catches(std::runtime_error) IAAction::getName(int index);
%catches(std::runtime_error) IAAction::toString();

%catches(std::runtime_error) IAComponent::isNull();
%catches(std::runtime_error) IAComponent::getBackground();
%catches(std::runtime_error) IAComponent::getForeground();
%catches(std::runtime_error) IAComponent::getLocationInParent();
%catches(std::runtime_error) IAComponent::toString();

%catches(std::runtime_error) IAHyperlink::isNull();
%catches(std::runtime_error) IAHyperlink::getStartIndex();
%catches(std::runtime_error) IAHyperlink::getEndIndex();
%catches(std::runtime_error) IAHyperlink::getAnchorTarget(long index);
%catches(std::runtime_error) IAHyperlink::toString();

%catches(std::runtime_error) IATable2::isNull();
%catches(std::runtime_error) IATable2::getNColumns();
%catches(std::runtime_error) IATable2::getNRows();
%catches(std::runtime_error) IATable2::toString();

%catches(std::runtime_error) IATableCell::isNull();
%catches(std::runtime_error) IATableCell::getColumnExtent();
%catches(std::runtime_error) IATableCell::getColumnIndex();
%catches(std::runtime_error) IATableCell::getRowExtent();
%catches(std::runtime_error) IATableCell::getRowIndex();
%catches(std::runtime_error) IATableCell::toString();

%catches(std::runtime_error) IAText::isNull();
%catches(std::runtime_error) IAText::getCaretOffset();
%catches(std::runtime_error) IAText::getNCharacters();
%catches(std::runtime_error) IAText::getText(long start_offset, long end_offset);
%catches(std::runtime_error) IAText::toString();

%catches(std::runtime_error) IAValue::isNull();
%catches(std::runtime_error) IAValue::getCurrentValue();
%catches(std::runtime_error) IAValue::getMaximumValue();
%catches(std::runtime_error) IAValue::getMinimumValue();
%catches(std::runtime_error) IAValue::toString();

#define AXA_EXPORT
%include <axaccess/ia2/ia_2.h>
%include <axaccess/ia2/ia_action.h>
%include <axaccess/ia2/ia_component.h>
%include <axaccess/ia2/ia_hyperlink.h>
%include <axaccess/ia2/ia_node.h>
%include <axaccess/ia2/ia_table2.h>
%include <axaccess/ia2/ia_table_cell.h>
%include <axaccess/ia2/ia_text.h>
%include <axaccess/ia2/ia_value.h>
