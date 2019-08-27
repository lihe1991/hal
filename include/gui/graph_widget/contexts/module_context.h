#ifndef MODULE_CONTEXT_H
#define MODULE_CONTEXT_H

#include "netlist/module.h"

#include "gui/graph_widget/contexts/graph_context.h"

class module_layouter;
class module_shader;

class module_context final : public graph_context
{   
public:
    module_context(const std::shared_ptr<const module> m);

    bool contains_module(const u32 id) const override;
    bool contains_gate(const u32 id) const override;
    bool contains_net(const u32 id) const override;

    void add(const QSet<u32>& modules, const QSet<u32>& gates);
    void remove(const QSet<u32>& modules, const QSet<u32>& gates);
    //void net_change(const QSet<u32>& nets); // FIND BETTER NAME, IMPLEMENT

    bool node_for_gate(hal::node& node, const u32 id) const;

    u32 get_id() const;

    const QSet<u32>& modules() const;
    const QSet<u32>& gates() const;
    const QSet<u32>& internal_nets() const;
    const QSet<u32>& local_io_nets() const;
    const QSet<u32>& global_io_nets() const;

private:
    enum class layouter
    {
        standard = 0,
        minimal = 1
    };

    enum class shader
    {
        standard = 0
    };

    static module_layouter* create_layouter(const layouter type, module_context* const context);
    static module_shader* create_shader(const shader type, module_context* const context);

    static layouter s_default_layouter;
    static shader s_default_shader;

    void apply_changes() override;
    void evaluate_changes();

    const u32 m_id;

    QSet<u32> m_modules;
    QSet<u32> m_gates;
    QSet<u32> m_internal_nets;
    QSet<u32> m_local_io_nets;
    QSet<u32> m_global_io_nets;

    QSet<u32> m_added_modules;
    QSet<u32> m_added_gates;
    QSet<u32> m_added_internal_nets;
    QSet<u32> m_added_local_io_nets;
    QSet<u32> m_added_global_io_nets;

    QSet<u32> m_removed_modules;
    QSet<u32> m_removed_gates;
    QSet<u32> m_removed_internal_nets;
    QSet<u32> m_removed_local_io_nets;
    QSet<u32> m_removed_global_io_nets;

    layouter m_layouter_type;
};

#endif // MODULE_CONTEXT_H
