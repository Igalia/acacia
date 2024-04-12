%module acacia_atspi
%{
#include <acacia/atspi/atspi_interface.h>
#include <acacia/atspi/atspi_action_interface.h>
#include <acacia/atspi/atspi_component_interface.h>
#include <acacia/atspi/atspi_document_interface.h>
#include <acacia/atspi/atspi_hyperlink_interface.h>
#include <acacia/atspi/atspi_node.h>
#include <acacia/atspi/atspi_table_interface.h>
#include <acacia/atspi/atspi_table_cell_interface.h>
#include <acacia/atspi/atspi_text_interface.h>
#include <acacia/atspi/atspi_value_interface.h>
#include <acacia/atspi/linux_utils.h>

using namespace acacia;
%}

%include <std_except.i>
%include <std_pair.i>
%include <std_string.i>
%include <std_unique_ptr.i>
%include <std_vector.i>

namespace std {
  %template(AtspiNodeVector) vector<acacia::AtspiNode>;
  %template(AtspiStringVector) vector<std::string>;
  %template(AtspiPairIntInt) pair<int, int>;
};

%catches(std::runtime_error) acacia::AtspiNode::getRoleName() const;
%catches(std::runtime_error) acacia::AtspiNode::getName() const;
%catches(std::runtime_error) acacia::AtspiNode::getDescription() const;
%catches(std::runtime_error) acacia::AtspiNode::getAttributes() const;
%catches(std::runtime_error) acacia::AtspiNode::getInterfaces() const;
%catches(std::runtime_error) acacia::AtspiNode::getRelations() const;
%catches(std::runtime_error) acacia::AtspiNode::getTargetForRelationAtIndex(int relation_index, int target_index) const;
%catches(std::runtime_error) acacia::AtspiNode::getStates() const;
%catches(std::runtime_error) acacia::AtspiNode::getChildCount() const;
%catches(std::runtime_error) acacia::AtspiNode::getChildAtIndex(int index) const;
%catches(std::runtime_error) acacia::AtspiNode::getChildren() const;
%catches(std::runtime_error) acacia::AtspiNode::queryAction() const;
%catches(std::runtime_error) acacia::AtspiNode::queryComponent() const;
%catches(std::runtime_error) acacia::AtspiNode::queryDocument() const;
%catches(std::runtime_error) acacia::AtspiNode::queryHyperlink() const;
%catches(std::runtime_error) acacia::AtspiNode::queryTable() const;
%catches(std::runtime_error) acacia::AtspiNode::queryTableCell() const;
%catches(std::runtime_error) acacia::AtspiNode::queryText() const;
%catches(std::runtime_error) acacia::AtspiNode::queryValue() const;

%catches(std::runtime_error) acacia::AtspiActionInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiActionInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiActionInterface::getNActions() const;
%catches(std::runtime_error) acacia::AtspiActionInterface::getName(int index) const;
%catches(std::runtime_error) acacia::AtspiActionInterface::getDescription(int index) const;

%catches(std::runtime_error) acacia::AtspiComponentInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiComponentInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiComponentInterface::getPosition() const;
%catches(std::runtime_error) acacia::AtspiComponentInterface::getSize() const;

%catches(std::runtime_error) acacia::AtspiDocumentInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiDocumentInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiDocumentInterface::getDocumentAttributes() const;
%catches(std::runtime_error) acacia::AtspiDocumentInterface::getLocale() const;

%catches(std::runtime_error) acacia::AtspiHyperlinkInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiHyperlinkInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiHyperlinkInterface::getStartIndex() const;
%catches(std::runtime_error) acacia::AtspiHyperlinkInterface::getEndIndex() const;
%catches(std::runtime_error) acacia::AtspiHyperlinkInterface::getURI(int index) const;

%catches(std::runtime_error) acacia::AtspiTableInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiTableInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiTableInterface::getNColumns() const;
%catches(std::runtime_error) acacia::AtspiTableInterface::getNRows() const;

%catches(std::runtime_error) acacia::AtspiTextInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiTextInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiTextInterface::getCaretOffset() const;
%catches(std::runtime_error) acacia::AtspiTextInterface::getCharacterCount() const;
%catches(std::runtime_error) acacia::AtspiTextInterface::getText(int start_offset, int end_offset) const;

%catches(std::runtime_error) acacia::AtspiTableCellInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::getPosition() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::getColumnIndex() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::getColumnSpan() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::getRowIndex() const;
%catches(std::runtime_error) acacia::AtspiTableCellInterface::getRowSpan() const;

%catches(std::runtime_error) acacia::AtspiValueInterface::isNull() const;
%catches(std::runtime_error) acacia::AtspiValueInterface::toString() const;
%catches(std::runtime_error) acacia::AtspiValueInterface::getCurrentValue() const;
%catches(std::runtime_error) acacia::AtspiValueInterface::getMaximumValue() const;
%catches(std::runtime_error) acacia::AtspiValueInterface::getMinimumValue() const;

%include <acacia/atspi/atspi_interface.h>
%include <acacia/atspi/atspi_action_interface.h>
%include <acacia/atspi/atspi_component_interface.h>
%include <acacia/atspi/atspi_document_interface.h>
%include <acacia/atspi/atspi_hyperlink_interface.h>
%include <acacia/atspi/atspi_table_interface.h>
%include <acacia/atspi/atspi_table_cell_interface.h>
%include <acacia/atspi/atspi_text_interface.h>
%include <acacia/atspi/atspi_value_interface.h>
%include <acacia/atspi/atspi_node.h>
%include <acacia/atspi/linux_utils.h>
