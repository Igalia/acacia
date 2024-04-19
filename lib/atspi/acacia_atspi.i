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
%}

%include <std_except.i>
%include <std_pair.i>
%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AtspiNodeVector) vector<acacia::AtspiNode>;
  %template(AtspiStringVector) vector<std::string>;
  %template(AtspiPairIntInt) pair<int, int>;
};

%include <acacia/atspi/atspi_interface.h>

namespace acacia {
  // Nested classes aren't supported, but it's a private implementation detail so
  // we don't need it exposed to bindings anyway.
  %warnfilter(325) AtspiInterface::Deleter;

  %template(AtspiActionInterfaceTemplate) AtspiInterface<AtspiAction>;
  %template(AtspiComponentInterfaceTemplate) AtspiInterface<AtspiComponent>;
  %template(AtspiDocumentInterfaceTemplate) AtspiInterface<AtspiDocument>;
  %template(AtspiHyperlinkInterfaceTemplate) AtspiInterface<AtspiHyperlink>;
  %template(AtspiTableCellInterfaceTemplate) AtspiInterface<AtspiTableCell>;
  %template(AtspiTableInterfaceTemplate) AtspiInterface<AtspiTable>;
  %template(AtspiTextInterfaceTemplate) AtspiInterface<AtspiText>;
  %template(AtspiValueInterfaceTemplate) AtspiInterface<AtspiValue>;

  // SWIG complains about AtspiInterface not being an immediate base of these
  // classes, even though it is in each instance.
  %warnfilter(329) AtspiActionInterface;
  %warnfilter(329) AtspiComponentInterface;
  %warnfilter(329) AtspiDocumentInterface;
  %warnfilter(329) AtspiHyperlinkInterface;
  %warnfilter(329) AtspiTableCellInterface;
  %warnfilter(329) AtspiTableInterface;
  %warnfilter(329) AtspiTextInterface;
  %warnfilter(329) AtspiValueInterface;

  %catches(std::runtime_error) AtspiNode::getRoleName() const;
  %catches(std::runtime_error) AtspiNode::getName() const;
  %catches(std::runtime_error) AtspiNode::getDescription() const;
  %catches(std::runtime_error) AtspiNode::getAttributes() const;
  %catches(std::runtime_error) AtspiNode::getInterfaces() const;
  %catches(std::runtime_error) AtspiNode::getRelations() const;
  %catches(std::runtime_error) AtspiNode::getTargetForRelationAtIndex(int relation_index, int target_index) const;
  %catches(std::runtime_error) AtspiNode::getStates() const;
  %catches(std::runtime_error) AtspiNode::getChildCount() const;
  %catches(std::runtime_error) AtspiNode::getChildAtIndex(int index) const;
  %catches(std::runtime_error) AtspiNode::getChildren() const;
  %catches(std::runtime_error) AtspiNode::queryAction() const;
  %catches(std::runtime_error) AtspiNode::queryComponent() const;
  %catches(std::runtime_error) AtspiNode::queryDocument() const;
  %catches(std::runtime_error) AtspiNode::queryHyperlink() const;
  %catches(std::runtime_error) AtspiNode::queryTable() const;
  %catches(std::runtime_error) AtspiNode::queryTableCell() const;
  %catches(std::runtime_error) AtspiNode::queryText() const;
  %catches(std::runtime_error) AtspiNode::queryValue() const;

  %catches(std::runtime_error) AtspiActionInterface::isNull() const;
  %catches(std::runtime_error) AtspiActionInterface::toString() const;
  %catches(std::runtime_error) AtspiActionInterface::getNActions() const;
  %catches(std::runtime_error) AtspiActionInterface::getName(int index) const;
  %catches(std::runtime_error) AtspiActionInterface::getDescription(int index) const;

  %catches(std::runtime_error) AtspiComponentInterface::isNull() const;
  %catches(std::runtime_error) AtspiComponentInterface::toString() const;
  %catches(std::runtime_error) AtspiComponentInterface::getPosition() const;
  %catches(std::runtime_error) AtspiComponentInterface::getSize() const;

  %catches(std::runtime_error) AtspiDocumentInterface::isNull() const;
  %catches(std::runtime_error) AtspiDocumentInterface::toString() const;
  %catches(std::runtime_error) AtspiDocumentInterface::getDocumentAttributes() const;
  %catches(std::runtime_error) AtspiDocumentInterface::getLocale() const;

  %catches(std::runtime_error) AtspiHyperlinkInterface::isNull() const;
  %catches(std::runtime_error) AtspiHyperlinkInterface::toString() const;
  %catches(std::runtime_error) AtspiHyperlinkInterface::getStartIndex() const;
  %catches(std::runtime_error) AtspiHyperlinkInterface::getEndIndex() const;
  %catches(std::runtime_error) AtspiHyperlinkInterface::getURI(int index) const;

  %catches(std::runtime_error) AtspiTableInterface::isNull() const;
  %catches(std::runtime_error) AtspiTableInterface::toString() const;
  %catches(std::runtime_error) AtspiTableInterface::getNColumns() const;
  %catches(std::runtime_error) AtspiTableInterface::getNRows() const;

  %catches(std::runtime_error) AtspiTextInterface::isNull() const;
  %catches(std::runtime_error) AtspiTextInterface::toString() const;
  %catches(std::runtime_error) AtspiTextInterface::getCaretOffset() const;
  %catches(std::runtime_error) AtspiTextInterface::getCharacterCount() const;
  %catches(std::runtime_error) AtspiTextInterface::getText(int start_offset, int end_offset) const;

  %catches(std::runtime_error) AtspiTableCellInterface::isNull() const;
  %catches(std::runtime_error) AtspiTableCellInterface::toString() const;
  %catches(std::runtime_error) AtspiTableCellInterface::getPosition() const;
  %catches(std::runtime_error) AtspiTableCellInterface::getColumnIndex() const;
  %catches(std::runtime_error) AtspiTableCellInterface::getColumnSpan() const;
  %catches(std::runtime_error) AtspiTableCellInterface::getRowIndex() const;
  %catches(std::runtime_error) AtspiTableCellInterface::getRowSpan() const;

  %catches(std::runtime_error) AtspiValueInterface::isNull() const;
  %catches(std::runtime_error) AtspiValueInterface::toString() const;
  %catches(std::runtime_error) AtspiValueInterface::getCurrentValue() const;
  %catches(std::runtime_error) AtspiValueInterface::getMaximumValue() const;
  %catches(std::runtime_error) AtspiValueInterface::getMinimumValue() const;
}

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
