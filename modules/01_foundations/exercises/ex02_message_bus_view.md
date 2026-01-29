# ex02_message_bus_view – string_view overload

What you are building: `MessageBus::publish` overload accepting `std::string_view` to avoid allocations.
Why it matters: Hot paths must not allocate; ownership clarity prevents copies.

Prerequisites check
- `grep -n "class MessageBus" include/platform/message_bus.hpp` → class exists
- `ctest --preset dev -N | grep MessageBus` → tests visible

Files you will touch
- `include/platform/message_bus.hpp`
- `src/platform/message_bus.cpp`
- `tests/test_message_bus.cpp`

Steps
1. Add overload declaration:
```
sed -n '1,120p' include/platform/message_bus.hpp | head -n 5
```
Append below existing publish:
```
void publish(std::string_view topic, std::string_view payload) const;
```

2. Implement:
```
cat >> src/platform/message_bus.cpp <<'EOF'
void MessageBus::publish(std::string_view topic, std::string_view payload) const {
    Message msg{.topic = std::string(topic), .payload = std::string(payload)};
    publish(msg);
}
EOF
```
Expected: reuses existing path; copies happen once.

3. Add test:
```
cat >> tests/test_message_bus.cpp <<'EOF'
TEST(Module01, PublishStringView){ platform::MessageBus bus; std::atomic<int> c{0}; bus.subscribe("t",[&](const platform::Message& m){ if(m.payload=="x") c++; }); bus.publish("t","x"); EXPECT_EQ(c.load(),1); }
EOF
```

4. Build + run filtered tests:
```
cmake --build --preset dev --target platform_core_tests
ctest --preset dev -R Module01
```
Expected: 3/3 tests pass.

Verification
- `ctest --preset dev -R Module01` PASS
- `nm build/dev/libplatform_core.a | grep publish` shows overload exists (optional).

Stop here and commit
- Message: "Module01: add string_view publish"

If it fails
- Undefined symbol: ensure function signature matches declaration.
- Duplicate symbol: avoid multiple definitions; place implementation once.

Stretch goals
- Accept payload as `std::span<const std::byte>` for binary messages.
