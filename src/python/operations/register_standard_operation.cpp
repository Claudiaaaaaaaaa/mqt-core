#include "operations/StandardOperation.hpp"
#include "python/pybind11.hpp"

namespace mqt {

void registerStandardOperation(py::module& m) {
  py::class_<qc::StandardOperation, qc::Operation>(
      m, "StandardOperation",
      "Standard quantum operation. "
      "This class is used to represent all standard operations, i.e. "
      "operations that can be represented by a single gate. "
      "This includes all single qubit gates, as well as multi-qubit gates like "
      "CNOT, SWAP, etc. as well primitives like barriers.")
      .def(py::init<>(), "Create an empty standard operation. This is "
                         "equivalent to the identity gate.")
      .def(py::init<qc::Qubit, qc::OpType, std::vector<qc::fp>>(), "target"_a,
           "op_type"_a, "params"_a = std::vector<qc::fp>{},
           "Create a single-qubit standard operation of specified type.")
      .def(py::init<const qc::Targets&, qc::OpType, std::vector<qc::fp>>(),
           "targets"_a, "op_type"_a, "params"_a = std::vector<qc::fp>{},
           "Create a multi-qubit standard operation of specified type.")
      .def(py::init<qc::Control, qc::Qubit, qc::OpType,
                    const std::vector<qc::fp>&>(),
           "control"_a, "target"_a, "op_type"_a,
           "params"_a = std::vector<qc::fp>{},
           "Create a controlled standard operation of specified type.")
      .def(py::init<qc::Control, const qc::Targets&, qc::OpType,
                    const std::vector<qc::fp>&>(),
           "control"_a, "targets"_a, "op_type"_a,
           "params"_a = std::vector<qc::fp>{},
           "Create a controlled multi-target standard operation of specified "
           "type.")
      .def(py::init<const qc::Controls&, qc::Qubit, qc::OpType,
                    const std::vector<qc::fp>&>(),
           "controls"_a, "target"_a, "op_type"_a,
           "params"_a = std::vector<qc::fp>{},
           "Create a multi-controlled standard operation of specified type.")
      .def(py::init<const qc::Controls&, const qc::Targets&, qc::OpType,
                    std::vector<qc::fp>>(),
           "controls"_a, "targets"_a, "op_type"_a,
           "params"_a = std::vector<qc::fp>{},
           "Create a multi-controlled multi-target standard operation of "
           "specified type.")
      .def(py::init<const qc::Controls&, qc::Qubit, qc::Qubit, qc::OpType,
                    std::vector<qc::fp>>(),
           "controls"_a, "target0"_a, "target1"_a, "op_type"_a,
           "params"_a = std::vector<qc::fp>{},
           "Create a multi-controlled two-target operation of specified type.")
      .def("__repr__", [](const qc::StandardOperation& op) {
        std::stringstream ss;
        ss << "StandardOperation(";
        const auto& controls = op.getControls();
        if (controls.size() == 1U) {
          ss << "control=";
          const auto& control = *controls.begin();
          ss << control.toString() << ", ";
        } else if (!controls.empty()) {
          ss << "controls={";
          for (const auto& control : controls) {
            ss << control.toString() << ", ";
          }
          ss << "}, ";
        }
        const auto& targets = op.getTargets();
        if (targets.size() == 1U) {
          ss << "target=" << targets.front() << ", ";
        } else if (!targets.empty()) {
          ss << "targets=[";
          for (const auto& target : targets) {
            ss << target << ", ";
          }
          ss << "], ";
        }
        ss << "op_type=" << toString(op.getType());
        const auto& params = op.getParameter();
        if (!params.empty()) {
          ss << ", params=[";
          for (const auto& param : params) {
            ss << param << ", ";
          }
          ss << "]";
        }
        ss << ")";
        return ss.str();
      });
}
} // namespace mqt
