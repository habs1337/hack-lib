#include "../includes/includes.h"


namespace g_cheat::memory::hooks {

	uintptr_t vmt_data[10000] = { };
	size_t vtable_size = 0;


	c_vmt::c_vmt() {
		m_new_vtable = m_original_vtable = m_class_base = nullptr;
		m_current_vtable_size = 0;
		m_hooked_table = false;
	}

	void c_vmt::get_vtable_size() {
		//for (; m_original_vtable.add(sizeof(size_t) * m_current_vtable_size).as<c_address*>()->is_valid_ptr(); m_current_vtable_size++);
		for (; m_original_vtable.as<c_address*>()[m_current_vtable_size].is_valid(); m_current_vtable_size++);
	}

	bool c_vmt::init(void** class_base) {
		if (m_hooked_table) {
			return true;
		}

		m_class_base = class_base;

		if (!m_class_base.is_valid()) {
			return false;
		}

		//m_original_vtable = *class_base.to<c_address*>();
		m_original_vtable = *reinterpret_cast<c_address*>(class_base);

		//printf("\noriginal vtable:%llx\n", m_original_vtable);

		if (!m_original_vtable.is_valid()) {
			return false;
		}

		get_vtable_size();
		//printf("vtable size:%d\n", m_current_vtable_size);

		if (!m_current_vtable_size || m_current_vtable_size + vtable_size >= 10000) {
			return false;
		}

		//m_new_vtable = c_address(new std::uintptr_t[vtable_size]);
		 
		m_new_vtable = c_address(&vmt_data[vtable_size]);
		//m_new_vtable = new c_address[m_current_vtable_size];

		g_mini_crt::memory::mem_cpy(m_new_vtable, m_original_vtable, m_current_vtable_size * sizeof(c_address));
		
		vtable_size += m_current_vtable_size;

		//printf("new vtable:%llx\n", m_new_vtable);

		if (!m_new_vtable.is_valid()) {
			return false;
		}

		

		//class_base.as<c_address*>()->set(m_new_vtable);
		*reinterpret_cast<c_address*>(class_base) = m_new_vtable;

		m_hooked_table = true;

		return true;
	}

	void c_vmt::setup_hook(size_t index, void* function_ptr) {
		//retard control xD
		if (!m_hooked_table || index >= m_current_vtable_size || index < 0) {
			return;
		}

		m_new_vtable.as<c_address*>()[index] = (uintptr_t)function_ptr;
	}

	void c_vmt::disable_hook(size_t index) {

		if (!m_hooked_table || index >= m_current_vtable_size || index < 0) {
			return;
		}

		m_new_vtable.as<c_address*>()[index] = m_original_vtable.as<c_address*>()[index];
	}

	void c_vmt::unhook_vtable() {

		if (!m_hooked_table) {
			return;
		}

		//m_class_base.as<c_address*>()->set(m_original_vtable);
		m_class_base.set(m_original_vtable);
		m_hooked_table = false;
	}

}









/*
vmt example 
g_cheat::memory::c_module new_module_handle;
new_module_handle.find_module();

g_cheat::memory::c_address class_ptr_address = new_module_handle.find_pattern("\x48\x89\x05\x00\x00\x00\x00\x33\xC0\x83\xF8\x01", "xxx????xxxxx");
ñlass_ptr_address.relative32(7);
if (some_shit.init(class_ptr_address)) 
	some_shit.setup_hook(0, g_cheat::memory::hooks::c_vmt::force_cast(&hooked_function));
	
*/