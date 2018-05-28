[@bs.module "react-simple-maps"]
external geographies: ReasonReact.reactClass = "Geographies";

let make = (~geography : string, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=geographies,
    ~props={
        "geography" : geography,
    },
    children,
  );